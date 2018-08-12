open Dom;

type nodeName =
  | DIV
  | TEXT

type node = {
  name: nodeName,
  text: string,
  attributes: array((string, string)),
  children: list(node),
  null: bool,
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
  attributes: [||],
  children: [],
  null: false,
};

let div = (~id="", ~_class="", ~children, rest) : node => {
  name: DIV,
  text: "",
  attributes: [|("id", id), ("class", _class)|],
  children,
  null: false,
};

let rec render = (node: node) =>
  switch node.name {
    | TEXT => createTextNode(node.text)
    | DIV => createElement("div")
      |> setAttributes(node.attributes)
      |> appendChild(List.map(child => render(child), node.children))
  };

let component = (name, ~children) => (<div id="component"></div>);

let jsx = <div _class="cls" id="1">
  <div id="2" _class="cls1"></div>
  <div id="2" _class="cls1"></div>
  <div id="2" _class="cls1"></div>
  <div id="2" _class="cls1"></div>
  <div id="2" _class="cls1">
    <component />
    <div id="3" _class="cls1"></div>
    <div id="3" _class="cls1"></div>
    <div id="3" _class="cls1"></div>
    <div id="3" _class="cls1">(text("42"))</div>
  </div>
</div>

let app  = render(
  jsx
);
