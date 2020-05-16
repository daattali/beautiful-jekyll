var config = {
  startOnLoad: true,
  theme: 'forest',
  flowchart: {
    useMaxWidth: false,
    htmlLabels: true
  }
};
mermaid.initialize(config);
window.mermaid.init(undefined, document.querySelectorAll('.language-mermaid'));