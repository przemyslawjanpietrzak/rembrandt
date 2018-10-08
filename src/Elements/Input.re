open ElementFactory;
open ElementsTypes;
open Dom;

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