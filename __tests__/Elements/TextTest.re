open Jest;

open Rembrandt.Elements;

describe("Elements: Text", () => {
  open Expect;

  test("text should contains string from argument", () => {
    text("example text").text |> expect |> toEqual("example text");
  });

});
