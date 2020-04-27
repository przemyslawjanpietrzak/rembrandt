open ElementFactory;
open ElementsTypes;
open Dom;

let shadowRoot =
  (~children, _rest): node => generateShadowNode(~children, ());
