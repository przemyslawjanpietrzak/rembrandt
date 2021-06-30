open ElementFactory;
open ElementsTypes;

let shadowRoot = (~children, ~mode=ShadowDomOpenMode, ()): node =>
  generateShadowNode(~children, ~mode, ());
