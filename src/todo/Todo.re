let typeDefs =
  ApolloServer.gql(.
    {|
      type Query {
        getTodos: [Todo]
      }
      type Mutation {
          addTodo(input: AddTodoInput!): Todo!,
          updateTodo(input: UpdateTodoInput!): Todo!
      }
      type Todo {
          guid: ID!,
          description: String!,
          completed: Boolean!
      }
      input AddTodoInput {
          description: String!
      }
      input UpdateTodoInput {
          guid: ID!,
          description: String!,
          completed: Boolean!
      }
    |},
  );

module Resolvers = {
  [@bs.module] external uuid: unit => string = "uuid/v4";
  [@bs.set]
  external set_todo_description: (TodoType.todo, string) => TodoType.todo =
    "description";

  [@bs.set]
  external set_todo_completed: (TodoType.todo, bool) => TodoType.todo =
    "completed";

  let todos: TodoType.todos = [||];
  let resolvers =
    TodoType.resolvers(
      ~query=TodoType.todoQuery(~getTodos=() => todos),
      ~mutation=
        TodoType.todoMutation(
          ~addTodo=
            (_obj, args) => {
              let input = args->TodoType.inputGet;
              let newTodo =
                TodoType.todo(
                  ~guid=uuid(),
                  ~description=input->TodoType.descriptionGet,
                  ~completed=false,
                );
              Belt.Array.concat(todos, [|newTodo|]) |> ignore;
              newTodo;
            },
          ~updateTodo=
            (_obj, args) => {
              let input = args->TodoType.inputGet;
              let existingTodo =
                todos
                |> Js.Array.find(todo =>
                     todo->TodoType.guidGet == input->TodoType.guidGet
                   );
              let todo =
                Belt.Option.(
                  existingTodo
                  ->(
                      map(todo => {
                        set_todo_description(
                          todo,
                          input->TodoType.descriptionGet,
                        )
                        |> ignore;
                        set_todo_completed(todo, input->TodoType.completedGet)
                        |> ignore;
                        todo;
                      })
                    )
                  ->getExn
                );
              todo;
            },
        ),
    );
};