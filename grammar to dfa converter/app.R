# Conversor de gramática regular a DFA.
# Creado por:
# Rogelio Guzmán Cruzado A01639914
# Fernanda Elizabeth Romo Alarcon A01639261


library(shiny)
library(igraph)

# Define UI para la aplicación que renderiza un autómata.
ui <- fluidPage(
  # Título.
  titlePanel("Conversor de gramática regular a DFA."),
  # Entrada de área de texto. 
  sidebarLayout(
    sidebarPanel(
      textAreaInput("grammar", "Escribe aquí tu gramática: ")
    ),
    
    # Renderiza el autómata y la gramática en texto.
    mainPanel(
      plotOutput("DFA"),
      verbatimTextOutput("Texto")
    )
  )
)

# Lógica para renderizar el autómata dependiendo de la gramática introducida.
server <- function(input, output) {
  
  output$DFA <- renderPlot({
    
    # Eliminar espacios y creamos lista con gramáticas
    cv <- input$grammar
    cv <- gsub(" ", "", cv, fixed = TRUE)
    linebreak <- strsplit(cv, "\n", TRUE)
    grammarlist <- linebreak[[1]]
    
    # Crear vectores vacíos.
    graphvector <- c()
    edge.labels <- c()
    colors <- c()
    uniqueVertices <- c()
    
    # Ciclo para iterar sobre toda la lista y dividir en derecha e izquierda
    for (reggrammar in grammarlist) {
      arrowsplit <- strsplit(reggrammar, "->", TRUE)
      leftright <- arrowsplit[[1]]
      variable <- leftright[1]
      destination <- leftright[2]
      terminal <- substr(destination, 0, 1)
      nonterminal <- substr(destination, nchar(destination), nchar(destination) + 1)
      
      # Evitar códigos de error cuando la gramática es incompleta.
      if (!is.na(variable) && !is.na(nonterminal)) {
        
        # Agregar izquierda y derecha a vectores.
        if (nchar(destination) == 1){
          nonterminal = "Z"
        }
        if (!(variable %in% uniqueVertices)) {
          uniqueVertices <- c(uniqueVertices, variable)
        }
        if (!(nonterminal %in% uniqueVertices)) {
          uniqueVertices <- c(uniqueVertices, nonterminal)
        }
    
        graphvector <- c(graphvector, variable, nonterminal)
        edge.labels <- c(edge.labels, terminal)
        
      }
    }
    
    # Agregar color a cada nodo dependiendo si es inicial, final o nada.
    for (vertices in uniqueVertices){
      if (vertices == "S"){
        colors <- c(colors, "green")
      }else if (vertices == "Z"){
        colors <- c(colors, "red")
      }else{
        colors <- c(colors, "white")
      }
    }
    
    # Graficar el autómata.
    
    g <- graph(graphvector, directed = TRUE)
    plot(g, edge.label = edge.labels, edge.arrow.mode = 2, edge.arrow.width = 1, edge.arrow.size = 1, 
         vertex.color = colors)

  })
  
  # Renderizar salida.
  output$Texto <- renderText({
    input$grammar
  })
}

# Correr aplicación.
shinyApp(ui = ui, server = server)