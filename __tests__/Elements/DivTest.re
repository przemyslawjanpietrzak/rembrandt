open Jest;

open Rembrandt.Elements;

describe("Elements: div", () => {
  open Expect;

  let filterEmpty = List.filter(((_, value)) => value !== "");

  test("<div /> should create node with class", () =>
    (<div _class="class-value" />).attributes
    |> filterEmpty
    |> expect
    |> toEqual([("class", "class-value")])
  );

  test("<div /> should create node with id", () =>
    (<div id="id-value" />).attributes
    |> filterEmpty
    |> expect
    |> toEqual([("id", "id-value")])
  );

  test("<div /> should create node with class & id", () =>
    (<div id="id-value" _class="class-value" />).attributes
    |> filterEmpty
    |> expect
    |> toEqual([("id", "id-value"), ("class", "class-value")])
  );
});