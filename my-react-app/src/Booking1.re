type trip =
  | OneWay(option(Js.Date.t))
  | RoundTrip(option(Js.Date.t), option(Js.Date.t));

let tripToString = x =>
  switch (x) {
  | OneWay(_) => "OneWay"
  | RoundTrip(_) => "RoundTrip"
  };

let isOneWay = x =>
  switch (x) {
  | OneWay(_) => true
  | RoundTrip(_) => false
  };

let debug = x => {
  let toString = date =>
    Belt.Option.(
      date->map(Js.Date.toDateString)->getWithDefault("not specified yet")
    );
  switch (x) {
  | OneWay(date) => "OneWay: " ++ toString(date)
  | RoundTrip(departure, return) =>
    "Round Trip: "
    ++ " (departure) "
    ++ toString(departure)
    ++ " (return): "
    ++ toString(return)
  };
};

let debugStateChange = (currentState, nextState) => {
  Js.log("###");
  Js.log("Current State: -");
  Js.log(debug(currentState));
  Js.log(debug(nextState));
  Js.log("###");
};

let s = React.string;

let formTargetValue = event => ReactEvent.Form.target(event)##value;
let isEmptyDateString = x => x |> Js.String.trim |> Js.String.length == 0;
let formattedDateValue = x =>
  x |> Js.Date.toISOString |> Js.String.slice(~from=0, ~to_=10);

//Validations

let isDateTodayorAfter = x => {
  let today = MomentRe.momentNow();
  let x = MomentRe.momentWithDate(x);
  MomentRe.Moment.isSameWithGranularity(x, today, `day)
  || MomentRe.Moment.isSameOrAfter(x, today);
};

[@react.component]
let make = (~name) => {
  let (state, setState) = React.useState(() => OneWay(None));
  // Handle function
  let handleDepartureDateChange = date => {
    let date = Js.Date.fromString(date);
    if (isDateTodayorAfter(date)) {
      let state' =
        switch (state) {
        | OneWay(_) => OneWay(Some(date))
        | RoundTrip(_, return) => RoundTrip(Some(date), return)
        };
      debugStateChange(state, state');
      setState(_ => state');
    };
  };

  let handleReturnDateChange = (departure, return) => {
    let return = Js.Date.fromString(return);
    let state' = RoundTrip(departure, Some(return));
    debugStateChange(state, state');
    setState(_ => state');
  };

  let handleTripChange = x =>
    switch (x) {
    | OneWay(departure) => RoundTrip(departure, None)
    | RoundTrip(departure, _return) => OneWay(departure)
    };

  let handleChange = _ => {
    let nextState = handleTripChange(state);
    debugStateChange(state, nextState);
    setState(_ => nextState);
  };

  let dateInput = (~label, ~handleDateChange, ~dateValue) =>
    <label>
      <p className="mb-2 text-center"> {s(label)} </p>
      <input
        className="border-2 border-gray-500"
        type_="date"
        value=Belt.Option.(
          dateValue->map(formattedDateValue)->getWithDefault("")
        )
        onChange={event => event |> formTargetValue |> handleDateChange}
      />
    </label>;
  let departOn = date =>
    <div className="mr-8">
      {dateInput(
         ~label="Depart On",
         ~handleDateChange=handleDepartureDateChange,
         ~dateValue=date,
       )}
    </div>;

  let returnOn = (departure, return) =>
    dateInput(
      ~label="Return On",
      ~handleDateChange=handleReturnDateChange(departure),
      ~dateValue=return,
    );
  let datePicker =
    switch (state) {
    | OneWay(departure) => departOn(departure)
    | RoundTrip(departure, return) =>
      <> {departOn(departure)} {returnOn(departure, return)} </>
    };
  <div className="bg-gray-200 h-screen">
    <h1 className="text-5x1 text-center"> {React.string("Booking")} </h1>
    <div className="p-8 flex items-center justify-center">
      <label className="mr-8">
        <input
          onChange=handleChange
          name
          value="OneWay"
          checked={isOneWay(state)}
          className="mr-2"
          type_="radio"
        />
        <span> {s("One Way")} </span>
      </label>
      <label>
        <input
          onChange=handleChange
          name
          value="RoundTrip"
          className="mr-2"
          checked={!isOneWay(state)}
          type_="radio"
        />
        <span> {s("Round Trip")} </span>
      </label>
    </div>
    <div className="flex justify-center"> datePicker </div>
  </div>;
};