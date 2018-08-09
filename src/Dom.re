type domElement;

[@bs.val]
external createElement : string => domElement = "document.createElement";

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
      return document.createTextNode(text);
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