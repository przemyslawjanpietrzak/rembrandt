open ElementFactory;
open ElementsTypes;
open Dom;

let form =
    (
      ~id="",
      ~_class="",
      ~style="",
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
