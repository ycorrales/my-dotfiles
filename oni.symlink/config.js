const activate = (oni) => {
   // access the Oni plugin API here

   // for example, unbind the default `<c-p>` action:
   //oni.input.unbind("<c-p>")

   // or bind a new action:
   //oni.input.bind("<c-p>", () => alert("Pressed control enter"));
};

module.exports = {
    activate,
    // change configuration values here:
    "oni.useDefaultConfig": false,
    "oni.loadInitVim": true,
    "editor.fontSize": "12px",
    "editor.fontFamily": "Meslo\ LG\ M\ DZ",
    "editor.completions.enabled": true
}
