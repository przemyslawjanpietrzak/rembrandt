open ElementsTypes;
open Dom;

let createNodeElement = (node, render, name) =>
  createElement(name)
  |> setAttributes(
       node.attributes |> List.filter(((_, value)) => value != ""),
     )
  |> setHandlers(node.handlers)
  |> appendChild(List.map(child => render(child), node.children));

let createShadowRootElement = (node, render, name) =>
  createShadowElement(name)
  |> setAttributes(
    node.attributes |> List.filter(((_, value)) => value != ""),
  )
  |> setHandlers(node.handlers)
  |> appendChildToShadowRoot(List.map(child => render(child), node.children));

let rec render = (node: node) =>
  switch (node.name) {
  | TEXT => createTextNode(node.text)
  | DIV => createNodeElement(node, render, "div")
  | SPAN => createNodeElement(node, render, "span")
  | Button => createNodeElement(node, render, "button")
  | Input => createNodeElement(node, render, "input")
  | Form => createNodeElement(node, render, "form")
  | A => createNodeElement(node, render, "a")
  | H1 => createNodeElement(node, render, "h1")
  | H2 => createNodeElement(node, render, "h2")
  | H3 => createNodeElement(node, render, "h3")
  | H4 => createNodeElement(node, render, "h4")
  | H5 => createNodeElement(node, render, "h5")
  | ShadowRoot => createShadowRootElement(node, render, "div")
  };