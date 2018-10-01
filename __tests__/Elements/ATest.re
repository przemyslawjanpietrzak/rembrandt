open Jest;

open Rembrandt.Elements;

describe("Elements: A", () =>
  Expect.(
    test("<a /> should create node with url", () =>
      (<a href="url" />).attributes
      |> List.filter(((_, value)) => value !== "")
      |> expect
      |> toEqual([("href", "url")])
    )
  )
);