package models

import play.api.libs.json._
import play.api.libs.json.JsValue

/**
 * Created by caro
 */

case class Person(name: String)

object Person{

  implicit val personFormat = Json.format[Person]

}
