open Dom;

type nodeName =
  | DIV
  | TEXT
  | SPAN
  | Button
  | Input
  | Form;

type attributes = list((string, string));

type node = {
  name: nodeName,
  text: string,
  mutable position: int,
  attributes,
  handlers: list((string, option(eventHandler))),
  children: list(node),
};

type textElement = string;

type element =
  | Node
  | TextElement;

let text = (s: string): node => {
  name: TEXT,
  text: s,
  position: 0,
  attributes: [],
  handlers: [],
  children: [],
};

let defaultHandler = _ => ();

let generateNode =
    (
      ~name: nodeName,
      ~text="",
      ~id,
      ~_class,
      ~style,
      ~key,
      ~value="",
      ~action="",
      ~method="",
      ~onClick,
      ~onChange=defaultHandler,
      ~onInput=defaultHandler,
      ~onSubmit=defaultHandler,
      ~children,
      ~_type="",
      (),
    )
    : node => {
  let r = {
    name,
    text,
    position: 0,
    attributes:
      [
        ("id", id),
        ("class", _class),
        ("style", style),
        ("key", key),
        ("type", _type),
        ("value", value),
        ("method", method),
        ("action", action),
      ],
    handlers: [
      ("click", onClick !== defaultHandler ? Some(onClick) : None),
      ("change", onChange !== defaultHandler ? Some(onChange) : None),
      ("input", onInput !== defaultHandler ? Some(onInput) : None),
      ("submit", onSubmit !== defaultHandler ? Some(onSubmit) : None),
    ],
    children,
  };
  children
  |> List.iter((child) => {
    if (child.name != TEXT) {
      r.position = r.position + child.position;
    }
    r.position = r.position + 1;
  })
  r;
};

let div =
    (
      ~id="",
      ~_class="",
      ~style="",
      ~key="",
      ~onClick: eventHandler=defaultHandler,
      ~children,
      _rest,
    )
    : node =>
  generateNode(
    ~name=DIV,
    ~id,
    ~_class,
    ~style,
    ~key,
    ~onClick,
    ~children,
    (),
  );

let input =
    (
      ~id="",
      ~_class="",
      ~style="",
      ~key="",
      ~value="",
      ~onClick: eventHandler=defaultHandler,
      ~onChange: eventHandler=defaultHandler,
      ~onInput: eventHandler=defaultHandler,
      ~children,
      _rest,
    )
    : node =>
  generateNode(
    ~name=Input,
    ~id,
    ~_class,
    ~style,
    ~key,
    ~value,
    ~children,
    ~onClick,
    ~onInput,
    ~onChange,
    (),
  );

let form =
    (
      ~id="",
      ~_class="",
      ~style="",
      ~key="",
      ~action="",
      ~method="",
      ~onClick: eventHandler=defaultHandler,
      ~onSubmit: eventHandler=defaultHandler,
      ~children,
      _rest,
    )
    : node =>
  generateNode(
    ~name=Form,
    ~id,
    ~_class,
    ~style,
    ~key,
    ~action,
    ~method,
    ~children,
    ~onClick,
    ~onSubmit,
    (),
  );

let span =
    (
      ~id="",
      ~_class="",
      ~style="",
      ~key="",
      ~onClick: eventHandler=defaultHandler,
      ~children,
      _rest,
    )
    : node =>
  generateNode(
    ~name=SPAN,
    ~id,
    ~_class,
    ~style,
    ~key,
    ~onClick,
    ~children,
    (),
  );

let button =
    (
      ~id="",
      ~_class="",
      ~style="",
      ~key="",
      ~onClick: eventHandler=defaultHandler,
      ~children,
      _rest,
    )
    : node =>
  generateNode(
    ~name=Button,
    ~text="",
    ~id,
    ~_class,
    ~style,
    ~key,
    ~onClick,
    ~children,
    (),
  );
