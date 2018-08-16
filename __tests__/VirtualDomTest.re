open Jest;
open Main;
open VirtualDom;

describe("diffProps", () => {
  open Expect;

  test("the same nodes should return empty list", () =>
    diffProps(<div></div>, <div></div>)
      |> expect
      |> toEqual([]))

  test("removed class return empty string", () =>
      diffProps(<div _class="value"></div>, <div></div>)
        |> expect
        |> toEqual([("class", "")]))

  test("added class return added key and value", () =>
      diffProps(<div></div>, <div _class="value"></div>)
          |> expect
          |> toEqual([("class", "value")]))

  test("added attribures return this attributes", () =>
      diffProps(<div></div>, <div _class="value" id="id-value"></div>)
          |> expect
          |> toEqual([("id", "id-value"), ("class", "value")]))

});

/* describe("walker", () => {
  open Expect;

  let oldNode = <div></div>;
  let newNode = Some(<div></div>);

  test("toBe", () =>
  walker(~oldNode=oldNode, ~newNode=newNode, ~index=0)
    |> expect
    |> toEqual([[{ patchType: "replace", content: None, attributes: Some([]) }]]))

  test("toBe", () =>
    walker(
      ~oldNode=<div></div>,
      ~newNode=None,
      ~index=0,
    )
      |> List.flatten
      |> expect
      |> toEqual([]))

  test("toBe", () =>
      walker(
        ~oldNode=<div>{ text("43") }</div>,
        ~newNode=Some(<div>{ text("43") }</div>),
        ~index=0,
      )
        |> List.flatten
        |> expect
        |> toEqual([]))
}); */



/* describe("Expect.Operators", () => {
    open Expect;
    open! Expect.Operators;

    test("==", () =>
      expect(1 + 2) === 3)
  }
); */