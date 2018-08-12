type domElement = {
  children: list(domElement),
  childNodes: list(domElement),
};

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

let replaceChild: (domElement, domElement, domElement) => domElement = [%bs.raw
    {|
        function(parent, newNode, oldNode) {
            return parent.replaceChild(newNode, oldNode);
        }
    |}
];

let init: (string, domElement) => domElement = [%bs.raw
  {|
    function(id, element) {
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

let removeChild: (domElement, domElement) => domElement = [%bs.raw
    {|
      function(parent, child) {
        return parent.removeChild(child);
      }
  |}
]

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
