type node = {
  name: string,
  attributes: array((string, string)),
  children: list(node),
};

type element;
type document;

let div = (~id="", ~_class="", ~children, rest) : node => {
  name: "div",
  attributes: [|("id", id), ("class", _class)|],
  children,
};

[@bs.val]
external createElement : string => element = "document.createElement";

let setAttributes: (array((string, string)), element) => element = [%bs.raw
  {|
 function (attributes, element) {
	for (let i=0; i <attributes.length; i++) {
      element.setAttribute(attributes[i][0], attributes[i][1]);
   }
   return element;
 }
|}
];

let init: (element, string) => element = [%bs.raw
  {|
    function(element, id) {
      return document.getElementById(id).appendChild(element);
    }
|}
];

let appendChild: (list(element), element) => element = [%bs.raw
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
  createElement(node.name)
    |> setAttributes(node.attributes)
    |> appendChild(List.map(child => render(child), node.children))


let jsx = <div _class="cls" id="1">
  <div id="2" _class="cls1"></div>
  <div id="2" _class="cls1"></div>
  <div id="2" _class="cls1"></div>

  <div id="2" _class="cls1"></div>

  <div id="2" _class="cls1">
    <div id="3" _class="cls1"></div>
    <div id="3" _class="cls1"></div>

    <div id="3" _class="cls1"></div>

    <div id="3" _class="cls1"></div>

  </div>
</div>

let app  = render(
  jsx
);
