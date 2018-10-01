open Dom;

type nodeName =
  | DIV
  | TEXT
  | SPAN
  | Button
  | Input
  | Form
  | A;

type attributes = list((string, string));

type node = {
  name: nodeName,
  text: string,
  mutable position: int,
  attributes,
  handlers: list((string, option(eventHandler))),
  children: list(node),
};