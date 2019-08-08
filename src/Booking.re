type state =
  | OneWay
  | RoundTrip;

let stateToString =
  fun
  | OneWay => "OneWay"
  | RoundTrip => "RoundTrip";

let s = React.string;

let formTargetValue = event => ReactEvent.Form.target(event)##value;

[@react.component]
let make = (~name) => {
  let (state, setState) = React.useState(() => OneWay);

  let handleChange = (state, _) => {
    setState(_ => state);
  };

  let dateInput = (~label, ~handleDateChange) =>
    <label>
      <p className="mb-2 text-center"> {s(label)} </p>
      <input
        className="border-2 border-gray-500"
        type_="date"
        onChange={event =>
          event |> formTargetValue |> Js.Date.fromString |> handleDateChange
        }
      />
    </label>;

  let handleDepartureDateChange = date =>
    Js.log("This is departure date: " ++ Js.Date.toISOString(date));

  let handleReturnDateChange = date =>
    Js.log("This is return date: " ++ Js.Date.toISOString(date));

  let departOn =
    <div className="mr-8">
      {dateInput(
         ~label="Depart On",
         ~handleDateChange=handleDepartureDateChange,
       )}
    </div>;

  let returnOn =
    dateInput(~label="Return On", ~handleDateChange=handleReturnDateChange);

  let datePicker = state =>
    switch (state) {
    | OneWay => departOn
    | RoundTrip => <> departOn returnOn </>
    };

  <div className="bg-gray-200 h-screen">
    <h1 className="text-5xl text-center"> {s("Booking")} </h1>
    <div className="p-8 flex items-center justify-center">
      <label className="mr-8">
        <input
          onChange={handleChange(OneWay)}
          name
          value={stateToString(OneWay)}
          checked={OneWay == state}
          className="mr-2"
          type_="radio"
        />
        <span> {s("OneWay")} </span>
      </label>
      <label>
        <input
          onChange={handleChange(RoundTrip)}
          name
          className="mr-2"
          value={stateToString(RoundTrip)}
          checked={RoundTrip == state}
          type_="radio"
        />
        <span> {s("RoundTrip")} </span>
      </label>
    </div>
    <div className="flex items-center justify-center">
      {datePicker(state)}
    </div>
  </div>;
};