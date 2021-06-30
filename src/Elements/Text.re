open ElementsTypes;

let text = (s: string): node => {
  name: TEXT,
  text: s,
  position: 0,
  attributes: [],
  handlers: [],
  children: [],
  shadowDomMode: None,
};
