open Jest;

describe("Example test scenario", () => {
  open Expect;

  test("example test", () =>
    42 |> expect |> toEqual(42)
  );

});