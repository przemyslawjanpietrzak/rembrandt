open Dom;

type nodeName =
  | DIV
  | TEXT
  | SPAN
  | Button
  | Input;

type attributes = list((string, string));

type node = {
  name: nodeName,
  text: string,
  mutable position: int,
  attributes,
  handlers: list((string, option(eventHandler))),
  children: list(node),
};

type textElement = string;

type element =
  | Node
  | TextElement;

let text = (s: string): node => {
  name: TEXT,
  text: s,
  position: 0,
  attributes: [],
  handlers: [],
  children: [],
};

let defaultHandler = _ => false |> ignore;

let generateNode = (~name: nodeName, ~text="", ~id, ~_class, ~style, ~key, ~onClick, ~onChange=defaultHandler, ~onInput=defaultHandler, ~children, ~_type="", ()): node => {
  name,
  text,
  position: 0,
  attributes:
    [("id", id), ("class", _class), ("style", style), ("key", key), ("type", _type)]
    |> List.filter(((_, value)) => value !== ""),
  handlers: [
    ("click", onClick !== defaultHandler ? Some(onClick) : None),
    ("change", onChange !== defaultHandler ? Some(onChange) : None),
    ("input", onInput !== defaultHandler ? Some(onChange) : None),
  ],
  children,
};

let input =
    (
      ~id="",
      ~_class="",
      ~style="",
      ~key="",
      ~_type="",
      ~onClick: eventHandler=defaultHandler,
      ~onInput: eventHandler=defaultHandler,
      ~children,
      _rest,
    ): node => generateNode(~name=Input, ~id, ~_class, ~style, ~key, ~onClick, ~children, ~onInput, ~_type, ());

let div =
    (
      ~id="",
      ~_class="",
      ~style="",
      ~key="",
      ~onClick: eventHandler=defaultHandler,
      ~children,
      _rest,
    ): node => generateNode(~name=DIV, ~id, ~_class, ~style, ~key, ~onClick, ~children, ());

let span =
    (
      ~id="",
      ~_class="",
      ~style="",
      ~key="",
      ~onClick: eventHandler=defaultHandler,
      ~children,
      _rest,
    ): node => generateNode(~name=SPAN,  ~id, ~_class, ~style, ~key, ~onClick, ~children, ());

let button =
    (
      ~id="",
      ~_class="",
      ~style="",
      ~key="",
      ~onClick: eventHandler=defaultHandler,
      ~children,
      _rest,
    ): node => generateNode(~name=Button, ~text="", ~id, ~_class, ~style, ~key, ~onClick, ~children, ());

let createNodeElement = (node, render, name) => createElement(name)
  |> setAttributes(node.attributes)
  |> setHandlers(node.handlers)
  |> appendChild(List.map(child => render(child), node.children))

let rec render = (node: node) =>
  switch (node.name) {
  | TEXT => createTextNode(node.text)
  | DIV => createNodeElement(node, render, "div")
  | SPAN => createNodeElement(node, render, "span")
  | Button => createNodeElement(node, render, "button")
  | Input => createNodeElement(node, render, "input")
};