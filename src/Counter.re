[@react.component]
let make = () => {
  let (count, setCount) = React.useState(() => 0);

  let handlePlusOne = _event => setCount(_ => count + 1);

  let handleMinusOne = _event => setCount(_ => count - 1);

  <div className="flex justify-center items-center bg-blue-200 p-8">
    <button
      onClick=handleMinusOne
      className="py-2 px-2 border border-red-400 hover:border-red-600 text-red-400 hover:text-red-600 mr-4">
      {React.string("-")}
    </button>
    <p className="mr-4"> {count |> string_of_int |> React.string} </p>
    <button
      onClick=handlePlusOne
      className="py-2 px-2 border border-red-400 hover:border-red-600 text-red-400 hover:text-red-600 mr-4">
      {React.string("+")}
    </button>
  </div>;
};