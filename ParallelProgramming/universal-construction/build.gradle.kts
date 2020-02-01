import org.jetbrains.kotlin.gradle.plugin.*

buildscript {
    repositories {
        jcenter()
    }
    dependencies {
        classpath("org.jetbrains.kotlinx:atomicfu-gradle-plugin:0.13.2")
    }
}

plugins {
    kotlin("jvm") version "1.3.50"
    java
}

apply(plugin = "kotlinx-atomicfu")

group = "ru.ifmo.mpp"
version = "1.0-SNAPSHOT"

repositories {
    jcenter()
    maven("https://kotlin.bintray.com/kotlinx/")
    maven("https://dl.bintray.com/devexperts/Maven")
}

dependencies {
    implementation(kotlin("stdlib-jdk8"))
    testImplementation(kotlin("test-junit"))
    testImplementation("org.jetbrains.kotlinx:lincheck:2.4")
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

// This is needed for the current version of AtomicFu that does not support Java 11 bytecode
java {
    sourceCompatibility = JavaVersion.VERSION_1_8
    targetCompatibility = JavaVersion.VERSION_1_8
}
