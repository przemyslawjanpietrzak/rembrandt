open ElementFactory;
open ElementsTypes;
open Dom;

let shadowRoot =
  (~children, ~mode=ShadowDomOpenMode, ()): node => generateShadowNode(~children, ~mode, ());
