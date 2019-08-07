[@react.component]
let make = (~initial, ~step) => {
  let (count, setCount) = React.useState(() => initial);

  let handlePlusStep = _event => setCount(_ => count + step);

  let handleMinusStep = _event => setCount(_ => count - step);

  <div className="flex justify-center items-center bg-blue-200 p-8">
    <button
      onClick=handleMinusStep
      className="py-2 px-2 border border-red-400 hover:border-red-600 text-red-400 hover:text-red-600 mr-4">
      {React.string("-")}
    </button>
    <p className="mr-4 text-blue-400 hover:text-blue-600">
      {count |> string_of_int |> React.string}
    </p>
    <button
      onClick=handlePlusStep
      className="py-2 px-2 border border-red-400 hover:border-red-600 text-red-400 hover:text-red-600 mr-4">
      {React.string("+")}
    </button>
  </div>;
};