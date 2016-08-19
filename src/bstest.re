let module React = {
  type obj;
  type eventDOM;
  type event = | OnClick;
  type eventHandler = {handler: 'e .'e => unit};
  type inlineStyle = | Style 'a :inlineStyle;
  type opaqueJsProps = | Props 'jsProps :opaqueJsProps | Nothing :opaqueJsProps;
  type domElement = {
    tag: string,
    props: opaqueJsProps
    /* styleString: option string,
       style: option inlineStyle,
       className: option string,
       eventHandlers: list (string, eventDOM => unit) */
  };
  type element 'props 'state = {form: form 'props 'state, children: list opaqueElement}
  and opaqueElement = | OpaqueElement (element 'props 'state) :opaqueElement
  and elementDescription 'props 'state = {
    initProps: 'props,
    getInitialState: 'props => 'state,
    componentWillMount: reactInstance 'props 'state => unit,
    componentDidMount: reactInstance 'props 'state => unit,
    componentWillReceiveProps: 'props => reactInstance 'props 'state => unit,
    shouldComponentUpdate: 'props => 'state => reactInstance 'props 'state => bool,
    componentWillUpdate: 'props => 'state => reactInstance 'props 'state => unit,
    componentDidUpdate: 'props => 'state => reactInstance 'props 'state => unit,
    componentWillUnmount: reactInstance 'props 'state => unit,
    render: reactInstance 'props 'state => opaqueElement,
    createInstanceFromJs: 'props => 'state => ('state => unit) => reactInstance 'props 'state,
    /* 'props => 'state => r 'props 'state => reactInstance 'props 'state, */
    createStateFromJs: 'state => 'state,
    createPropsFromJs: 'props => 'props
    /* createUpdaterInstanceFromJs: 'props => 'state => updaterInstance 'props 'state */
  }
  and form 'props 'state =
    | DOMElement domElement | ReactElement (elementDescription 'props 'state) | TextNode string
  /* TODO unify updaterInstance & reactInstance */
  /* and updaterInstance 'props 'state = {pprops: 'props, sstate: 'state} */
  and r 'props 'state = {apply: 'a .(reactInstance 'props 'state => 'a => 'state) => 'a => unit}
  and reactInstance 'props 'state = {props: 'props, state: 'state, setState: 'state => unit} /* updater: r 'props 'state */
  /* opaqueReactInstance => Gadt wrapped descriptor, helpfull when returning GADTs that hide their heterogeneous types */
  and opaqueReactInstance = | OpaqueInstance (reactInstance 'p 's) :opaqueReactInstance;
  /* let unpack: opaqueElement => element = fun opaque => sw */
  /*type opaqueElement is a GADT wrapped descriptor, helpfull when returning GADTs that hide their heterogeneous types */
  let module Text = {
    let make: string => opaqueElement = fun t => OpaqueElement {form: TextNode t, children: []};
  };
  /*  external make_config_args : tag::string =>
      className::string? =>
      style::'a? =>
      onCopy::('clipboard => unit)? =>
      onCut::('clipboard => unit)? =>
      onPaste::('clipboard => unit)? =>
      onCompositionEnd::('composition => unit)? =>
      onCompositionStart::('composition => unit)? =>
      onCompositionUpdate::('composition => unit)? =>
      onKeyDown::('keyboard => unit)? =>
      onKeyPress::('keyboard => unit)? =>
      onKeyUp::('keyboard => unit)? =>
      onFocus::('focus => unit)? =>
      onBlur::('focus => unit)? =>
      onChange::('form => unit)? =>
      onInput::('form => unit)? =>
      onSubmit::('form => unit)? =>
      onClick::('mouse => unit)? =>
      onContextMenu::('mouse => unit)? =>
      onDoubleClick::('mouse => unit)? =>
      onDrag::('mouse => unit)? =>
      onDragEnd::('mouse => unit)? =>
      onDragEnter::('mouse => unit)? =>
      onDragExit::('mouse => unit)? =>
      onDragLeave::('mouse => unit)? =>
      onDragOver::('mouse => unit)? =>
      onDragStart::('mouse => unit)? =>
      onMouseDown::('mouse => unit)? =>
      onMouseEnter::('mouse => unit)? =>
      onMouseLeave::('mouse => unit)? =>
      onMouseMove::('mouse => unit)? =>
      onMouseOut::('mouse => unit)? =>
      onMouseOver::('mouse => unit)? =>
      onMouseUp::('mouse => unit)? =>
      onSelect::('selection => unit)? =>
      onTouchCancel::('touch => unit)? =>
      onTouchEnd::('touch => unit)? =>
      onTouchMove::('touch => unit)? =>
      onTouchStart::('touch => unit)? =>
      onScroll::('ui => unit)? =>
      onWheel::('wheel => unit)? =>
      onAbort::('media => unit)? =>
      onCanPlay::('media => unit)? =>
      onCanPlayThrough::('media => unit)? =>
      onDurationChange::('media => unit)? =>
      onEmptied::('media => unit)? =>
      onEncrypted::('media => unit)? =>
      onEnded::('media => unit)? =>
      onError::('media => unit)? =>
      onLoadedData::('media => unit)? =>
      onLoadedMetadata::('media => unit)? =>
      onLoadStart::('media => unit)? =>
      onPause::('media => unit)? =>
      onPlay::('media => unit)? =>
      onPlaying::('media => unit)? =>
      onProgress::('media => unit)? =>
      onRateChange::('media => unit)? =>
      onSeeked::('media => unit)? =>
      onSeeking::('media => unit)? =>
      onStalled::('media => unit)? =>
      onSuspend::('media => unit)? =>
      onTimeUpdate::('media => unit)? =>
      onVolumeChange::('media => unit)? =>
      onWaiting::('media => unit)? =>
      onAbort::('media => unit)? =>
      onLoad::('image => unit)? =>
      onError::('image => unit)? =>
      onAnimationStart::('animation => unit)? =>
      onAnimationEnd::('animation => unit)? =>
      onAnimationIteration::('animation => unit)? =>
      onTransitionEnd::('transition => unit)? =>
      children::list opaqueElement =>
      't = "" [@@bs.obj]; */
  module type DOMComponent = {
    let tag: string;
    /* let make:
       style::inlineStyle? =>
       styleString::string? =>
       className::string? =>
       onClick::(eventDOM => unit)? =>
       events::list (string, eventDOM => unit)? =>
       list opaqueElement =>
       opaqueElement; */
    let make: props::'a? => list opaqueElement => opaqueElement;
  };
  let module CreateDOMComponent (D: {let tag: string;}) :DOMComponent => {
    let tag = D.tag;
    /* let make
           style::style=?
           styleString::styleString=?
           className::className=?
           onClick::onClick=?
           events::events=?
           children => {
         let eventHandlers =
           switch events {
           | None => []
           | Some eventHandlers => eventHandlers
           };
         let element = DOMElement {tag, styleString, style, eventHandlers, className};
         OpaqueElement {form: element, children}
       }; */
    let make props::props=? children => {
      let props =
        switch props {
        | None => Nothing
        | Some props => Props props
        };
      let element = DOMElement {tag, props};
      OpaqueElement {form: element, children}
    };
  };
  let module DefaultLifeCycle = {
    let getInitialState: 'props => 'state = fun p => ();
    let componentWillMount: reactInstance 'props 'state => unit = fun this => ();
    let componentDidMount: reactInstance 'props 'state => unit = fun this => ();
    let componentWillReceiveProps: 'props => reactInstance 'props 'state => unit =
      fun nextProps this => ();
    let shouldComponentUpdate: 'props => 'state => reactInstance 'props 'state => bool =
      fun nextProps nextState this => true;
    let componentWillUpdate: 'props => 'state => reactInstance 'props 'state => unit =
      fun nextProps nextState this => ();
    let componentDidUpdate: 'props => 'state => reactInstance 'props 'state => unit =
      fun prevProps prevState this => ();
    let componentWillUnmount: reactInstance 'props 'state => unit = fun this => ();
  };
  let module Stateless (M: {type props;}) => {
    type props = M.props;
    type state = unit;
    include DefaultLifeCycle;
  };
  let module Stateful (M: {type props; type state;}) => {
    include M;
    include DefaultLifeCycle;
  };
  module type LifeCycleSignature = {
    type props;
    type state;
    let getInitialState: props => state;
    let componentWillMount: reactInstance props state => unit;
    let componentDidMount: reactInstance props state => unit;
    let componentWillReceiveProps: props => reactInstance props state => unit;
    let shouldComponentUpdate: props => state => reactInstance props state => bool;
    let componentWillUpdate: props => state => reactInstance props state => unit;
    let componentDidUpdate: props => state => reactInstance props state => unit;
    let componentWillUnmount: reactInstance props state => unit;
  };
  module type ComponentSpec = {
    include LifeCycleSignature;
    let render: reactInstance props state => opaqueElement;
  };
  module type Component = {
    include LifeCycleSignature;
    let make: children::list opaqueElement? => props::props => opaqueElement;
  };
  let module CreateComponent
             (Component: ComponentSpec)
             :(Component with type props = Component.props) => {
    include Component;
    let createInstanceFromJs props state setState => {props, state, setState};
    let createPropsFromJs props => props;
    let createStateFromJs state => state;
    let createStateFromJs state => state;
    /* let createUpdaterInstanceFromJs props state => {pprops: props, sstate: state}; */
    let make children::children=? props::props => {
      let description: elementDescription props state = {
        initProps: props,
        getInitialState,
        componentWillMount,
        componentDidMount,
        componentWillReceiveProps,
        shouldComponentUpdate,
        componentWillUpdate,
        componentDidUpdate,
        componentWillUnmount,
        render,
        /* createInstanceFromElement, */
        createInstanceFromJs,
        createStateFromJs,
        createPropsFromJs
        /* createUpdaterInstanceFromJs */
      };
      let element = ReactElement description;
      switch children {
      | None => OpaqueElement {form: element, children: []}
      | Some children => OpaqueElement {form: element, children}
      }
    };
  };
  let module DOM = {
    let module H3 = CreateDOMComponent {
      let tag = "h3";
    };
    let module Div = CreateDOMComponent {
      let tag = "div";
    };
    let module Button = CreateDOMComponent {
      let tag = "button";
    };
    let module Ul = CreateDOMComponent {
      let tag = "ul";
    };
    let module Li = CreateDOMComponent {
      let tag = "li";
    };
  };
  /* let render: opaqueElement => string =
     fun tree => {
       let rec render' node =>
         switch node {
         | OpaqueElement unpackedElement =>
           let {form, children} = unpackedElement;
           switch form {
           | DOMElement {tag, style} =>
             let renderedChildren = String.concat "" (List.map (fun s => render' s) children);
             switch style {
             | Some style =>
               String.concat
                 "" ["<", tag, " style=\"", style, "\">", renderedChildren, "</", tag, ">"]
             | None => String.concat "" ["<", tag, ">", renderedChildren, "</", tag, ">"]
             }
           | TextNode text => text
           | ReactElement description =>
             let instance = {
               props: description.initProps,
               state: description.getInitialState description.initProps
             };
             let instance = {
               props: description.initProps,
               state: description.componentWillMount instance
             };
             let node = description.render instance;
             render' node
           }
         };
       render' tree
     }; */
};

open React;

type counterProps = {initialCount: int};

type counterState = {count: int};

let module Counter = CreateComponent {
  include Stateful {
    type props = counterProps;
    type state = counterState;
  };
  let handleUpClick {state: {count}} event => {
    let nextState = {count: count + 1};
    nextState
  };
  let handleDownClick {state: {count}} _ => {count: count - 1};
  let computeDown currentCount => {count: currentCount - 1};
  let handleClick _ => Js.log "Just log to the console";
  let handleDoubleClick _ => Js.log "Just clicked 2x";
  let getInitialState {initialCount} => {count: initialCount};
  let componentWillMount {state, setState} => setState {count: state.count + 100};
  let componentDidMount _ => Js.log "mounted the counter!";
  let computeUp currentCount => {count: currentCount + 1};
  let render {props: {initialCount}, state: {count}, setState} => DOM.Div.make [
    DOM.Div.make [Text.make ("Initial count (from props): " ^ string_of_int initialCount)],
    DOM.Div.make [Text.make ("Current count (state): " ^ string_of_int count)],
    DOM.Button.make
      props::[%bs.obj {onClick: fun _ => setState (computeUp count)}] [Text.make "Up!"],
    DOM.Button.make
      props::[%bs.obj {onClick: fun _ => setState (computeDown count)}] [Text.make "Down!"],
    DOM.Button.make
      props::[%bs.obj
        {onClick: handleClick, onDoubleClick: handleDoubleClick, onMouseOver: handleClick}
      ]
      [Text.make "Do not click here!"]
  ];
  /* let render {props: {initialCount}, state: {count}, updater} => DOM.Div.make [
       DOM.Div.make
         style::style [Text.make ("Initial count (from props): " ^ string_of_int initialCount)],
       DOM.Div.make [Text.make ("Current count (state): " ^ string_of_int count)],
       DOM.Button.make events::[("onClick", updater.apply handleUpClick)] [Text.make "Up!"],
       DOM.Button.make events::[("onClick", updater.apply handleDownClick)] [Text.make "Down!"],
       DOM.Button.make
         style::(Style [%bs.obj {color: "red", border: "1px solid blue"}])
         events::[("onClick", handleClick), ("onDoubleClick", handleDoubleClick)]
         [Text.make "Do not click here!"],

     ]; */
};

let module Birthday = {
  type t = {day: int, month: int, year: int};
  let make day::day month::month year::year => {day, month, year};
  let pprint {day, month, year} =>
    string_of_int day ^ "/" ^ string_of_int month ^ "/" ^ string_of_int year;
};

type user = {id: int, name: string, birthday: Birthday.t};

let userList = [
  {id: 0, name: "Kate", birthday: Birthday.make 24 10 1988},
  {id: 1, name: "David", birthday: Birthday.make year::1988 day::17 month::12}
];

let module UserDetail = CreateComponent {
  include Stateless {
    type props = option user;
  };
  let render {props} => {
    let message =
      switch props {
      | None => "No user selected"
      | Some {id, name, birthday} =>
        "id: " ^ string_of_int id ^ ", Name: " ^ name ^ ", Birthday: " ^ Birthday.pprint birthday
      };
    DOM.Div.make [DOM.Div.make [Text.make "selected user:"], DOM.Div.make [Text.make message]]
  };
};

type userItemProps = {user: user, onUserClick: user => unit};

let module UserItem = CreateComponent {
  include Stateless {
    type props = userItemProps;
  };
  let render {props: {user, onUserClick}} =>
    /* DOM.Li.make onClick::(fun _ => onUserClick user) [Text.make ("Name: " ^ user.name)]; */
    DOM.Li.make
      props::[%bs.obj {onClick: fun _ => onUserClick user}] [Text.make ("Name: " ^ user.name)];
};

type userPanelState = {selectedUser: option user};

let module UserPanel = CreateComponent {
  include Stateful {
    type props = list user;
    type state = userPanelState;
  };
  let selectUser _ newUser => {selectedUser: Some newUser};
  let getInitialState _ => {selectedUser: None};
  let render {props, state: {selectedUser}, setState} => DOM.Div.make [
    DOM.H3.make [Text.make "User Panel:"],
    DOM.Ul.make (
      List.map
        (
          fun user => UserItem.make {
            user,
            onUserClick: fun user => setState {selectedUser: Some user}
          }
        )
        props
    ),
    UserDetail.make selectedUser
  ];
};

type titleProps = string;

let module Title = CreateComponent {
  include Stateless {
    type props = titleProps;
  };
  let titleStyle = "border: 1px solid black; padding: 10px; width: 290px;";
  let render {props} => DOM.H3.make [Text.make ("Title: " ^ props)];
};

type domNode;

external getElementById : string => domNode = "document.getElementById" [@@bs.val];

let module ReactDOM = {
  type reactJsElement;
  type reactJsClass;
  external createElement : 'elementType => 'props => 'children => reactJsElement = "createElement" [@@bs.val] [@@bs.module
                                                                    "./polyfill.js"
                                                                    ];
  external render : reactJsElement => domNode => unit = "render" [@@bs.val] [@@bs.module
                                                                    "react-dom"
                                                                    ];
  external createClass : 'classSpec => reactJsClass = "createClass" [@@bs.val] [@@bs.module
                                                                    "react"
                                                                    ];
  type jsState;
  type jsProps;
  external makeJsState : reasonmlState::'a => jsState = "" [@@bs.obj];
  external makeJsProps : reasonmlProps::'a => jsProps = "" [@@bs.obj];
  type reactJsInstance;
  external setState : 'a => 'state => unit = "setState" [@@bs.send];
  external getState : 'a => 'b = "state" [@@bs.get];
  external getReasonmlState : 'a => 'b = "reasonmlState" [@@bs.get];
  external getProps : 'a => 'b = "props" [@@bs.get];
  external getReasonmlProps : 'a => 'b = "reasonmlProps" [@@bs.get];
  external makeClassNameProps : className::string? => onClick::'a? => unit => jsProps = "" [@@bs.obj];
  /* external makeEventHandlerProps : onClick::('a => unit) => unit => 't = "" [@@bs.obj] */
  external buildEventHandlers : 'a => 'eventProps = "buildEventHandlers" [@@bs.val] [@@bs.module
                                                                    "./polyfill.js"
                                                                    ];
  external mergeProps : 'a => 'b => 'c => 'd = "mergeProps" [@@bs.val] [@@bs.module
                                                                    "./polyfill.js"
                                                                    ];
  let buildJsTree tree => {
    let rec build node =>
      switch node {
      | OpaqueElement unpackedElement =>
        let {form, children} = unpackedElement;
        switch form {
        | DOMElement {tag, props} =>
          let jsChildren = List.map (fun c => build c) children |> Array.of_list;
          switch props {
          | Nothing => createElement tag Js.Null.empty jsChildren
          | Props props => createElement tag props jsChildren
          }
        /* let eventHandlerProps = buildEventHandlers (Array.of_list eventHandlers);
           let classProps =
             switch className {
             | None => makeClassNameProps ()
             | Some clss => makeClassNameProps className::clss ()
             };
           switch style {
           | None =>
             createElement tag (mergeProps classProps [%bs.obj {}] eventHandlerProps) jsChildren
           | Some style =>
             switch style {
             | Style s =>
               let style = [%bs.obj {style: s}];
               createElement tag (mergeProps classProps style eventHandlerProps) jsChildren
             }
           } */
        /* applyChildren createElementFn Js.Null.empty tag Js.Null.empty jsChildren */
        | TextNode text => createElement "span" Js.Null.empty text
        | ReactElement description =>
          let description_to_reactClass description => {
            let makeInstance reactJsThis => {
              let props = getReasonmlProps (getProps reactJsThis);
              let state = getReasonmlState (getState reactJsThis);
              /* let rec createUpdater () f => {
                   let handler event => {
                     let nextState =
                       f
                         (
                           description.createInstanceFromJs
                             props state {apply: fun f => createUpdater f}
                         )
                         event;
                     setState reactJsThis (makeJsState nextState)
                   };
                   handler
                 }; */
              let setSt state => setState reactJsThis (makeJsState state);
              description.createInstanceFromJs props state setSt
              /* {apply: fun f => createUpdater f} */
            };
            let spec =
              {
                method getInitialState props => {
                  let st = description.getInitialState description.initProps;
                  makeJsState st
                };
                method componentWillMount () => description.componentWillMount (makeInstance this);
                method componentDidMount () => description.componentDidMount (makeInstance this);
                method componentWillReceiveProps nextProps => {
                  let nextProps = description.createPropsFromJs nextProps;
                  description.componentWillReceiveProps nextProps (makeInstance this)
                };
                method shouldComponentUpdate nextProps nextState => {
                  let nextProps = description.createPropsFromJs nextProps;
                  let nextState = description.createStateFromJs nextState;
                  description.shouldComponentUpdate nextProps nextState (makeInstance this)
                };
                method componentWillUpdate nextProps nextState => {
                  let nextProps = description.createPropsFromJs nextProps;
                  let nextState = description.createStateFromJs nextState;
                  description.componentWillUpdate nextProps nextState (makeInstance this)
                };
                method componentDidUpdate prevProps prevState => {
                  let prevProps = description.createPropsFromJs prevProps;
                  let prevState = description.createStateFromJs prevState;
                  description.componentDidUpdate prevProps prevState (makeInstance this)
                };
                method componentWillUnmount () => description.componentWillUnmount (
                  makeInstance this
                );
                method render () => build (description.render (makeInstance this))
              }
              [@bs];
            createClass spec
          };
          let jsProps = makeJsProps description.initProps;
          let reactClass = description_to_reactClass description;
          createElement reactClass jsProps Js.Null.empty
        }
      };
    build tree
  };
  let render component::component node::node => render (buildJsTree component) node;
};

let app = DOM.Div.make [
  Title.make "Counter",
  Counter.make {initialCount: 0},
  UserPanel.make userList
];

let rootNode = getElementById "app";

ReactDOM.render app rootNode;