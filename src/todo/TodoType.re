type obj;

[@bs.deriving abstract]
type todo = {
  guid: string,
  description: string,
  completed: bool,
};

[@bs.deriving abstract]
type args = {input: todo};

type todos = array(todo);

[@bs.deriving abstract]
type todoQuery = {getTodos: unit => todos};

[@bs.deriving abstract]
type todoMutation = {
  addTodo: (obj, args) => todo,
  updateTodo: (obj, args) => todo,
};

[@bs.deriving abstract]
type resolvers = {
  [@bs.as "Query"]
  query: todoQuery,
  [@bs.as "Mutation"]
  mutation: todoMutation,
};