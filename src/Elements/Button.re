open ElementFactory;
open ElementsTypes;
open Dom;

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
