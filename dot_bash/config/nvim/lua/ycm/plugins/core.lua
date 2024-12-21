local fn = vim.fn

return {
  {
    "rhysd/vim-clang-format",
  },
  "vim-syntastic/syntastic",
  "PeterRincker/vim-searchlight",
  "benmills/vimux",
  {
    "iamcco/markdown-preview.nvim",
    cmd = { "MarkdownPreviewToggle", "MarkdownPreview", "MarkdownPreviewStop" },
    ft = { "markdown" },
    build = function() fn["mkdp#util#install"]() end,
  },
}
