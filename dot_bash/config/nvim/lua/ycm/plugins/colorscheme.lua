return {
  -- vim-one theme
  {
    "rakr/vim-one",
    name = "vim-one",
    lazy = true,
    enabled = true,
    opt = {
      one_allowitalics = 1, --- I love italic for comments
    },
  },
  -- Catppuccin theme
  {
    "catppuccin/nvim",
    name = "catppuccin",
    lazy = true,
    enabled = false,
    opts = {
      flavour = "mocha", -- latte, frappe, macchiato, mocha
      dim_inactive = { enabled = true, shade = "dark", percentage = 0.6 },
      transparent_background = false,
      term_colors = true,
      compile = { enabled = true, path = vim.fn.stdpath("cache") .. "/catppuccin", suffix = "_compiled" },
      styles = {
        comments = { "italic" },
        conditionals = { "italic" },
        loops = {},
        functions = { "bold" },
        keywords = {},
        strings = {},
        variables = {},
        numbers = {},
        booleans = {},
        properties = {},
        types = {},
        operators = {},
      },
      color_overrides = {
        macchiato = {
          text = "#C1C9E6",
          subtext1 = "#A3AAC2",
          subtext0 = "#8E94AB",
          overlay2 = "#7D8296",
          overlay1 = "#676B80",
          overlay0 = "#464957",
          surface2 = "#3A3D4A",
          surface1 = "#2F313D",
          surface0 = "#1D1E29",
          base = "#0b0b12",
          mantle = "#11111a",
          crust = "#191926",
        },
      },
      integrations = {
        treesitter = true,
        cmp = true,
        gitsigns = true,
        lsp_trouble = true,
        mason = true,
        markdown = true,
        native_lsp = {
          enabled = true,
          virtual_text = {
            errors = { "italic" },
            hints = { "italic" },
            warnings = { "italic" },
            information = { "italic" },
          },
          underlines = {
            errors = { "underline" },
            hints = { "underline" },
            warnings = { "underline" },
            information = { "underline" },
          },
        },
        neotree = true,
        noice = true,
        notify = true,
        telescope = {
          enabled = true,
          style = "nvchad",
        },
        treesitter_context = true,
        which_key = true,
        ts_rainbow = true,
      },
    },
  },
}
