name := """play-scala-app"""

version := "1.0-SNAPSHOT"

lazy val root = (project in file(".")).enablePlugins(PlayScala)

scalaVersion := "2.10.1"

herokuAppName in Compile := "still-brook-9566"

libraryDependencies ++= Seq(
  jdbc,
  anorm,
  cache,
  ws,
  "org.sorm-framework"%"sorm"%"0.3.8",
  "com.h2database" % "h2" % "1.3.168"
)
