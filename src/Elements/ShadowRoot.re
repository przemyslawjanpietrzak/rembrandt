open ElementFactory;
open ElementsTypes;
open Dom;

let shadowRoot =
  (~key, ~children, _rest) : node => (
    generateShadowNode(
      ~key,
      ~children,
      (),
    )
  );
