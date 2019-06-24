/* State declaration */
type state = {
  count: int,
  show: bool,
};

/* Action declaration */
type action =
  | Click
  | Toggle;

[@react.component]



let make = (~greeting) => {

  let reducer = (state, action) =>
  switch (action) {
  | Click => {...state, count: state.count + 1}
  | Toggle => {...state, show: ! state.show}
  }

  let (state, dispatch) = React.useReducer(reducer, {count: 0, show: true});

  let message =
    "You've clicked this " ++ string_of_int(state.count) ++ " times(s)";
  <div>
  // compared to hooks, we don't dispatch type:'sth'
  // but just the name of our Action variant (Click or Toggle')
    <button onClick={_event => dispatch(Click)}>
      {ReasonReact.string(message)}
    </button>
    <button onClick={_event => dispatch(Toggle)}>
      {ReasonReact.string("Toggle greeting")}
    </button>
    // see how ternatires work here - ReasonReact.null !
    {state.show ? ReasonReact.string(greeting) : ReasonReact.null}
  </div>;
};
