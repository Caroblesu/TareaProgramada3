package controllers

import models.{DB, Person}
import play.api._
import play.api.data.Form
import play.api.data.Forms._
import play.api.libs.json._
import play.api.mvc._


object Application extends Controller {

  def index = Action {
    Ok(views.html.index("Android Application."))
  }

   val personForm: Form[Person] = Form {
    mapping(
      "name" -> text
    )(Person.apply)(Person.unapply)
  }

  def addPerson = Action { implicit request =>
    val person = personForm.bindFromRequest.get
    DB.save(person)
    Redirect(routes.Application.index())
  }

  def getPersons = Action {

   val persons = DB.query[Person].fetch
    Ok(Json.toJson(persons))
  }



  //Json Preguntas
  case class Etiquetas(etiq1: String, etiq2: String)
  case class Respuestas(resp1: String, resp2: String, resp3: String)
  case class Place(pregunta: String, etiquetas: Etiquetas, respuestas: Seq[Respuestas])

  implicit val etiquetasWrites = new Writes[Etiquetas] {
    def writes(etiquetas: Etiquetas) = Json.obj(
      "etiqueta 1" -> etiquetas.etiq1,
      "etiqueta 2" -> etiquetas.etiq2
    )
  }
  implicit val respuesyasWrites = new Writes[Respuestas] {
    def writes(respuestas: Respuestas) = Json.obj(
      "Respuesta 1" -> respuestas.resp1,
      "Respuesta 2" -> respuestas.resp2,
      "Respuesta 3" -> respuestas.resp3
    )
  }
  implicit val placeWrites = new Writes[Place] {
    def writes(place: Place) = Json.obj(
      "Pregunta" -> place.pregunta,
      "Etiquetas" -> place.etiquetas,
      "Respuestas" -> place.respuestas)
  }

  val place = Place(
    "¿Cómo se hace una aplicación para Android?",
    Etiquetas("Aplicacion", "Android"),
    Seq(
      Respuestas("Bajar Android Studios", "Saber sobre lenguaje Java", "")
    )
  )

  val json1 = Json.toJson(place)
    def json = Action {
    Ok(Json.toJson(json1))
  }


  //Json Usuario Login
  case class Nombre(nombre: String, password:String)
  case class Usuario(nombre:Seq[Nombre])

  implicit val nombreWrites = new Writes[Nombre] {
    def writes(nombre: Nombre) = Json.obj(
      "Nombre Usuario" -> nombre.nombre,
      "Password Usuario" -> nombre.password
    )
  }

  implicit val usuarioWrites = new Writes[Usuario] {
    def writes(usuario: Usuario) = Json.obj(
        "Usuario" -> usuario.nombre
    )
  }

  val ingreso = Usuario(
  Seq(
    Nombre("Carolina", "Lenguajes2014"),
    Nombre("Kenneth", "Isabella"))
  )

  val json2 = Json.toJson(ingreso)
  def ingresar = Action {
    Ok(Json.toJson(json2))
  }


 }