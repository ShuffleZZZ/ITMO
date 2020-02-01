import org.jetbrains.kotlin.gradle.plugin.*

plugins {
    kotlin("jvm") version "1.3.50"
}

group = "ru.ifmo.mpp"
version = "1.0-SNAPSHOT"

repositories {
    jcenter()
    maven("https://kotlin.bintray.com/kotlinx")
    maven("https://dl.bintray.com/devexperts/Maven")
}

dependencies {
    implementation(kotlin("stdlib-jdk8"))
    testImplementation(kotlin("test-junit"))
    testImplementation("org.jetbrains.kotlinx:lincheck:2.5.2")
}

sourceSets {
    main {
        java.setSrcDirs(listOf("src"))
        withConvention(KotlinSourceSet::class) {
            kotlin.setSrcDirs(listOf("src"))
        }
    }
    test {
        withConvention(KotlinSourceSet::class) {
            kotlin.setSrcDirs(listOf("test"))
        }
    }
}
