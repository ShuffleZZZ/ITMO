import org.jetbrains.kotlin.gradle.plugin.*

plugins {
    kotlin("jvm") version "1.3.50"
    java
    application
}

group = "ru.ifmo.mpp"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    implementation(kotlin("stdlib-jdk8"))
}

sourceSets {
    main {
        java.setSrcDirs(listOf("src"))
        withConvention(KotlinSourceSet::class) {
            kotlin.setSrcDirs(listOf("src"))
        }
    }
}

application {
    mainClassName = "VerifyMonotoniсСlockKt"
}

tasks["build"].dependsOn("run")