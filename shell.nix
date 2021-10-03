with import <nixpkgs> { };

mkShell {
  buildInputs = [
    jekyll
    rubyPackages.jekyll-paginate
  ];
  shellHook = ''
      exec jekyll serve --watch --incremental
  '';
}
