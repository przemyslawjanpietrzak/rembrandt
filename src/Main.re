type nodeName =
  | DIV
  | TEXT

type node = {
  name: nodeName,
  text: string,
  attributes: array((string, string)),
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
type domElement;

let text = (s: string) : node => {
  name: TEXT,
  text: s,
  attributes: [||],
  children: [],
};

let div = (~id="", ~_class="", ~children, rest) : node => {
  name: DIV,
  text: "",
  attributes: [|("id", id), ("class", _class)|],
  children,
};


[@bs.val]
external createElement : nodeName => domElement = "document.createElement";

let setAttributes: (array((string, string)), domElement) => domElement = [%bs.raw
  {|
 function (attributes, element) {
	for (let i=0; i <attributes.length; i++) {
      element.setAttribute(attributes[i][0], attributes[i][1]);
   }
   return element;
 }
|}
];

let init: (domElement, string) => domElement = [%bs.raw
  {|
    function(element, id) {
      return document.getElementById(id).appendChild(element);
    }
|}
];

let createTextNode: (string) => domElement = [%bs.raw
  {|
    function(text) {
      return document.createTestNode(text);
    }
|}
];

let appendChild: (list(domElement), domElement) => domElement = [%bs.raw
  {|
   function (children, parent) {
      for (let i=0; i < children.length; i++) {
        if (Array.isArray(children[i])) {
          appendChild(children[i], parent);
        } else if (typeof children[i] !== 'number') {
          parent.appendChild(children[i]);
        }
      }
      return parent;
   }
|}
];

let rec render = (node: node) =>
  switch node.name {
    | TEXT => createTextNode(node.text)
    | DIV => createElement(node.name)
      |> setAttributes(node.attributes)
      |> appendChild(List.map(child => render(child), node.children))
  };


let jsx = <div _class="cls" id="1">
  <div id="2" _class="cls1"></div>
  <div id="2" _class="cls1"></div>
  <div id="2" _class="cls1"></div>

  <div id="2" _class="cls1"></div>

  <div id="2" _class="cls1">
    <div id="3" _class="cls1"></div>
    <div id="3" _class="cls1"></div>

    <div id="3" _class="cls1"></div>

    <div id="3" _class="cls1">(text("text"))</div>

  </div>
</div>

let app  = render(
  jsx
);
