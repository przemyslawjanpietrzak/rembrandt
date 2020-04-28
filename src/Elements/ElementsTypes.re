open Dom;

type nodeName =
  | DIV
  | TEXT
  | SPAN
  | Button
  | Input
  | Form
  | A
  | H1
  | H2
  | H3
  | H4
  | H5
  | SHADOW_ROOT;

type attributes = list((string, string));

type shadowDomMode =
  | ShadowDomOpenMode
  | ShadowDomCloseMode;

type node = {
  name: nodeName,
  text: string,
  mutable position: int,
  attributes,
  handlers: list((string, option(eventHandler))),
  children: list(node),
  shadowDomMode: option(shadowDomMode),
};
