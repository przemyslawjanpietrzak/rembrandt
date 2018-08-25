open Dom;

type nodeName =
  | DIV
  | TEXT
  | SPAN
  | Null

type attributes = list((string, string));

type node = {
  name: nodeName,
  text: string,
  mutable position: int,
  attributes: attributes,
  handlers: list((string, option(eventHandler))),
  children: list(node),
};

type textElement = string;

type element =
  | Node
  | TextElement;

let text = (s: string) : node => {
  name: TEXT,
  text: s,
  position: 0,
  attributes: [],
  handlers: [],
  children: [],
};

let defaultHandler = (a: string) => false;
let div = (~id="", ~_class="", ~style="", ~key="", ~onClick: eventHandler=defaultHandler, ~children, rest) : node => {
  name: DIV,
  text: "",
  position: 0,
  attributes: [("id", id), ("class", _class), ("style", style), ("key", key)],
  handlers: [("click", onClick !== defaultHandler ? Some(onClick) : None)],
  children,
};
let span = (~id="", ~_class="", ~style="", ~key="", ~onClick: eventHandler=defaultHandler, ~children, rest) : node => {
  name: SPAN,
  text: "",
  position: 0,
  attributes: [("id", id), ("class", _class), ("style", style), ("key", key)],
  handlers: [("click", onClick !== defaultHandler ? Some(onClick) : None)],
  children,
};

let null = (): node => {
  name: Null,
  text: "",
  position: 0,
  attributes: [],
  handlers: [],
  children: [],
};

let rec render = (node: node) =>
  switch node.name { /* TODO: */
    | TEXT => createTextNode(node.text)
    | DIV => createElement("div")
      |> setAttributes(node.attributes)
      |> setHandlers(node.handlers)
      |> appendChild(List.map(child => render(child), node.children))
    | SPAN => createElement("span")
      |> setAttributes(node.attributes)
      |> setHandlers(node.handlers)
      |> appendChild(List.map(child => render(child), node.children))
  };
