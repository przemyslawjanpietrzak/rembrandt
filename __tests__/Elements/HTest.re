open Jest;

open Rembrandt.Elements;

describe("Elements: h", () => {
  open Expect;

  let filterEmpty = List.filter(((_, value)) => value !== "");

  test("<h1 /> should create node", () =>
    (<h1 />).attributes |> filterEmpty |> expect |> toEqual([])
  );

  test("<h2 /> should create node", () =>
    (<h2 />).attributes |> filterEmpty |> expect |> toEqual([])
  );

  test("<h3 /> should create node", () =>
    (<h3 />).attributes |> filterEmpty |> expect |> toEqual([])
  );

  test("<h4 /> should create node", () =>
    (<h4 />).attributes |> filterEmpty |> expect |> toEqual([])
  );

  test("<h5 /> should create node", () =>
    (<h5 />).attributes |> filterEmpty |> expect |> toEqual([])
  );
});