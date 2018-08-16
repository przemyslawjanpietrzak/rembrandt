open Dom;

type nodeName =
  | DIV
  | TEXT
  | Null

type node = {
  name: nodeName,
  text: string,
  attributes: list((string, string)),
  handlers: list((string, option(eventHandler))),
  children: list(node),
};

type nodeChild =
  | Node
  | String;

type textElement = string;

type element =
  | Node
  | TextElement;

type document;

type template = (string, unit) => node;

type component = {
  createElement: template
}

let text = (s: string) : node => {
  name: TEXT,
  text: s,
  attributes: [],
  handlers: [],
  children: [],
};

let defaultHandler = (a: string) => false;
let div = (~id="", ~_class="", ~style="", ~onClick: eventHandler=defaultHandler, ~children, rest) : node => {
  name: DIV,
  text: "",
  attributes: [("id", id), ("class", _class), ("style", style)],
  handlers: [("click", onClick !== defaultHandler ? Some(onClick) : None)],
  children,
};

let null = (): node => {
  name: Null,
  text: "",
  attributes: [],
  handlers: [],
  children: [],
};


let rec render = (node: node) =>
  switch node.name {
    | TEXT => createTextNode(node.text)
    | DIV => createElement("div")
      |> setAttributes(node.attributes)
      |> setHandlers(node.handlers)
      |> appendChild(List.map(child => render(child), node.children))
  };

let component = (name, ~children) => (<div id="component"></div>);