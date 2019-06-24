type state = {
  seconds: int,
  isTicking: bool,
};

type action =
  | Start
  | Stop
  | Reset
  | Tick;

module Button = {
  [@react.component]
  let make = (~label, ~onClick) => {
    <button onClick> {label |> ReasonReact.string} </button>;
  };
};

[@react.component]
let make = () => {
  let reducer = (state, action) =>
    switch (action) {
    | Start => {...state, isTicking: true}
    | Stop => {...state, isTicking: false}
    | Reset => {...state, seconds: 30}
    | Tick =>
      state.isTicking && state.seconds > 0
        ? {...state, seconds: state.seconds - 1} : state
    };

  let initState = {isTicking: false, seconds: 30};
  let (state, dispatch) = React.useReducer(reducer, initState);

  // Reason instead asks you to also list the number of elements you care about
  // so no elementa after effect => we use useEffect0
  React.useEffect0(() => {
    let timerId = Js.Global.setInterval(() => dispatch(Tick), 1000);
    // unmount via Some
    Some(() => Js.Global.clearInterval(timerId));
  });

  <div>
    {ReasonReact.string(
       "There are " ++ string_of_int(state.seconds) ++ " on the clock",
     )}
    {state.isTicking
       ? <Button label="STOP" onClick={_event => dispatch(Stop)} />
       // note the Fragment below
       : <>
           <Button label="START" onClick={_event => dispatch(Start)} />
           <Button label="RESET" onClick={_event => dispatch(Reset)} />
         </>}
  </div>;
};