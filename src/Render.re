open ElementsTypes;
open Dom;

let createNodeElement = (node, render, name) =>
  createElement(name)
  |> setAttributes(node.attributes |> List.filter(((_, value)) => value != ""))
  |> setHandlers(node.handlers)
  |> appendChild(List.map(child => render(child), node.children));

let rec render = (node: node) =>
  switch (node.name) {
  | TEXT => createTextNode(node.text)
  | DIV => createNodeElement(node, render, "div")
  | SPAN => createNodeElement(node, render, "span")
  | Button => createNodeElement(node, render, "button")
  | Input => createNodeElement(node, render, "input")
  | Form => createNodeElement(node, render, "form")
  };