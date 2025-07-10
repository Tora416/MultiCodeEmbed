pluginManagement {
    repositories {
        maven { url = uri("https://maven.aliyun.com/repository/gradle-plugin/") }
        maven { url = uri("https://maven.aliyun.com/repository/public/") }
        maven { url = uri("https://repo1.maven.org/maven2/") }
        gradlePluginPortal()
        mavenCentral()
        // 添加额外的仓库来查找缺失的依赖
        maven { url = uri("https://oss.sonatype.org/content/repositories/snapshots/") }
        maven { url = uri("https://repository.apache.org/content/groups/public/") }
    }
}

rootProject.name = "astminer"