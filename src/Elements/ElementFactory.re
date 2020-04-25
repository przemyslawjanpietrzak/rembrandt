open Dom;

open ElementsTypes;

let defaultHandler = _ => ();

let generateShadowNode = (~key, ~children, ()): node => {
  let r = {
    name: DIV,
    text: "",
    position: 0,
    attributes: [
      ("key", key),
    ],
    handlers: [],
    children,
  };
  children
  |> List.iter(child => {
       if (child.name != TEXT) {
         r.position = r.position + child.position;
       };
       r.position = r.position + 1;
     });
  r;
};

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
      ~href="",
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
    attributes: [
      ("id", id),
      ("class", _class),
      ("style", style),
      ("key", key),
      ("type", _type),
      ("value", value),
      ("href", href),
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
  |> List.iter(child => {
       if (child.name != TEXT) {
         r.position = r.position + child.position;
       };
       r.position = r.position + 1;
     });
  r;
};
