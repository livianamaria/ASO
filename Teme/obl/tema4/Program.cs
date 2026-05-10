var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

List<TodoItem> todos = new List<TodoItem>();
int nextId = 1;

app.MapGet("/", () =>
{
    string html = """
    <html>
    <head>
        <title>TODO App</title>
    </head>
    <body>
        <h1>Aplicatie TODO</h1>

        <form method="post" action="/add">
            <input type="text" name="text" placeholder="Adauga task" required>
            <button type="submit">Adauga</button>
        </form>

        <hr>
    """;

    foreach (var todo in todos)
    {
        string status = todo.IsDone ? "terminat" : "neterminat";

        html += $"""
        <p>
            {todo.Id}. {todo.Text} - {status}
            <a href="/done/{todo.Id}">Marcheaza</a>
            <a href="/delete/{todo.Id}">Sterge</a>
        </p>
        """;
    }

    html += """
    </body>
    </html>
    """;

    return Results.Content(html, "text/html");
});

app.MapPost("/add", async (HttpRequest request) =>
{
    var form = await request.ReadFormAsync();
    string text = form["text"];

    //adauga un task nou in lista
    todos.Add(new TodoItem
    {
        Id = nextId++,
        Text = text,
        IsDone = false
    });

    return Results.Redirect("/");
});

app.MapGet("/done/{id}", (int id) =>
{
    var todo = todos.FirstOrDefault(t => t.Id == id);

    if (todo != null)
    {
        //schimba starea taskului
        todo.IsDone = !todo.IsDone;
    }

    return Results.Redirect("/");
});

app.MapGet("/delete/{id}", (int id) =>
{
    var todo = todos.FirstOrDefault(t => t.Id == id);

    if (todo != null)
    {
        //sterge taskul din lista
        todos.Remove(todo);
    }

    return Results.Redirect("/");
});

app.Run();

class TodoItem
{
    public int Id { get; set; }
    public string Text { get; set; } = "";
    public bool IsDone { get; set; }
}