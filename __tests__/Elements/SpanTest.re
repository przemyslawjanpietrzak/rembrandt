open Jest;

open Rembrandt.Elements;

describe("Elements: span", () => {
  open Expect;

  let filterEmpty = List.filter(((_, value)) => value !== "");

  test("<span /> should create node with class", () =>
    (<span _class="class-value" />).attributes
    |> filterEmpty
    |> expect
    |> toEqual([("class", "class-value")])
  );

  test("<span /> should create node with id", () =>
    (<span id="id-value" />).attributes
    |> filterEmpty
    |> expect
    |> toEqual([("id", "id-value")])
  );

  test("<span /> should create node with class & id", () =>
    (<span id="id-value" _class="class-value" />).attributes
    |> filterEmpty
    |> expect
    |> toEqual([("id", "id-value"), ("class", "class-value")])
  );
});