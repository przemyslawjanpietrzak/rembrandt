type node = {
  name: string,
  attributes: array((string, string)),
  children: list(node),
};

type element;
type document;

let div = (~id="", ~_class="", ~children, ()) : node => {
  name: "div",
  attributes: [|("id", id), ("class", _class)|],
  children,
};

[@bs.val]
external createElement : string => element = "document.createElement";

let setAttributes: (element, array((string, string))) => element = [%bs.raw {|
 function (element, attributes) {
	for (let i=0; i <attributes.lenght; i++) {
      element.setAttribute(attributes[i][0], attributes[i][1]);
   }
   return element;
 }
|}];

let appendChild: (element, list(element)) => element = [%bs.raw {|
   function (parent, child) {
      parent.appendChild(child);
      return parent;
   }
|}];

let rec render = (node: node) => {
  let children = List.map((child) => render(child), node.children);
  let element = createElement(node.name);
  appendChild(element, children);
  setAttributes(element, node.attributes);
};

let x = <div> <div id="4" /></div>;
