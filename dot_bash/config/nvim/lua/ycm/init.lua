require("ycm.globals")
local icons = require("ycm.assets").icons
local utils = require("ycm.utils")

---The config for the Ycm Neovim setup
---@class YcmConfig
---@field lazypath string|nil The path to load lazy.nvim from
---@field startup_art YcmAscii|nil The startup art to show when loading the app
---@field startup_color string|nil The color to use for the startup art
---@field zen boolean|nil Whether to show a minimal UI (hide statusline, line numbers, etc.)
---@field copilot boolean|nil Whether copilot is enabled
---@field avante boolean|nil Whether avante is enabled
---@field fzf boolean|nil Whether too configure fzf for tooling like telescope
---@field git boolean|nil Whether or not to configure the dotfiles for git
---@field prefer_git boolean|nil Whether to prefer using git for dependencies over other options like curl
---@field proxy string|nil A proxy URL to use for certain network functions
---@field colorscheme string|fun()|nil What to set the colorscheme to and/or how
local config = {
  --- Set lazy path to std vim data path ~/.local/share/nvim/lazy/lazy.nvim
  lazypath = vim.fn.stdpath("data") .. "lazy/lazy.nvim",
  startup_art = "nickycm",
  startup_color = "#653CAD",
  zen = true, --- ycm disable relative numbers
  copilot = false, --- ycm disable copilot
  avante = false,  --- ycm disable avante
  fzf = false,  --- ycm disable fzf
  git = true,
  proxy = nil,
  prefer_git = false,
  colorscheme = function()
    if utils.is_dark_mode() then
      vim.o.background = "dark"
    else
      vim.o.background = "light"
    end

    -- vim.cmd("colorscheme catppuccin")
    vim.cmd("colorscheme one")
  end,
}

---Assign a user config to the config table
---@param user_config? YcmConfig
local function assign_config(user_config)
  if user_config then
    for k, v in pairs(user_config) do
      config[k] = v
    end
  end
end

---@class ycmConfig
local M = {}
local lazy_loaded = false
local setup_called = false

local function load_lazy(path)
  --- if path does not exist
  if not (vim.uv or vim.loop).fs_stat(path) then
    local lazyrepo = "https://github.com/folke/lazy.nvim.git"
    local out = vim.fn.system({ "git", "clone", "--filter=blob:none", "--branch=stable", lazyrepo, path })
    if vim.v.shell_error ~= 0 then
      vim.api.nvim_echo({
        { "Failed to clone lazy.nvim:\n", "ErrorMsg" },
        { out, "WarningMsg" },
        { "\nPress any key to exit..." },
      }, true, {})
      vim.fn.getchar()
      os.exit(1)
    end
  end
  --- prepend path to vim runtime directory list
  vim.opt.rtp:prepend(path)
end

local plugins = {
  { import = "ycm.plugins" },
}

-- FIXME: fix the types
---@param plugin fun()|string|table
function M.add_plugin(plugin)
  table.insert(plugins, plugin)
end

---Load and configure neovim plugins using lazy.nvim
local function init_plugins()
  if lazy_loaded then
    return
  end

  local lazypath = config.lazypath or vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
  load_lazy(lazypath)

  if config.copilot then
    M.add_plugin({ import = "ycm.plugins.extras.copilot" })
  end

  if config.avante then
    M.add_plugin({ import = "ycm.plugins.extras.avante" })
  end

  -- if config.astro then
  --   table.insert(plugins, { import = "ycm.plugins.extras.astro" })
  -- end

  if config.fzf then
    M.add_plugin({ import = "ycm.plugins.extras.fzf" })
  end

  require("lazy").setup({
    spec = {
      -- import your plugins
      plugins,
    },
    -- Configure any other settings here. See the documentation for more details.
    -- colorscheme that will be used when installing plugins.
    install = { colorscheme = { "habamax" } },
    -- automatically check for plugin updates
    checker = { enabled = true },
  })

  lazy_loaded = true
end

---Apply syntax and LSP customizations
local function patch_syntax()
  -- set up custom symbols for LSP errors
  local signs = {
    Error = icons.error,
    Warning = icons.warning,
    Warn = icons.warning,
    Hint = icons.hint,
    Info = icons.hint,
  }
  for type, icon in pairs(signs) do
    local hl = "DiagnosticSign" .. type
    vim.fn.sign_define(hl, { text = icon, texthl = hl, numhl = hl })
  end

  vim.diagnostic.config({
    virtual_text = true,
    signs = true,
    update_in_insert = true,
    severity_sort = true,
  })

  -- make comments and HTML attributes italic
  vim.cmd([[highlight Comment cterm=italic term=italic gui=italic]])
  vim.cmd([[highlight htmlArg cterm=italic term=italic gui=italic]])
  vim.cmd([[highlight xmlAttrib cterm=italic term=italic gui=italic]])
  vim.cmd([[highlight Normal ctermbg=none]])
end

---Apply the colorscheme setting
---@param colorscheme string|fun() The colorscheme to apply
local function apply_colorscheme(colorscheme)
  if type(colorscheme) == "function" then
    colorscheme()
  else
    vim.cmd("colorscheme " .. colorscheme)
  end
end

---@param user_config? YcmConfig
function M.setup(user_config)
  if setup_called then
    -- only call setup once
    return
  end

  assign_config(user_config)
  if config.proxy then
    -- Set proxy environment variables for Neovim
    vim.env.http_proxy = config.proxy
    vim.env.https_proxy = config.proxy
  end

  require("ycm.config.filetype")
  require("ycm.config.options")
  require("ycm.config.keymaps")
  init_plugins()

  --- do these sctions after initializing the plugins
  apply_colorscheme(config.colorscheme)
  vim.cmd.syntax("on")
  vim.cmd("filetype plugin indent on")
  patch_syntax()
end

M.config = config

return M
