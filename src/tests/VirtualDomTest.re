open Jest;

open MyModule;

let () =
  describe "#myFunction"
    ExpectJs.(fun () => {
      test "some behavior" (fun () =>
        expect(MyModule.doSomething "withArgs") |> toEqual "expectedOutput"
      );
    })