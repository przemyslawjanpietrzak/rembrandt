let getValue: Dom.event => string = [%bs.raw
  {|
    function (e) {
      return e.target.value;
    }
  |}
];