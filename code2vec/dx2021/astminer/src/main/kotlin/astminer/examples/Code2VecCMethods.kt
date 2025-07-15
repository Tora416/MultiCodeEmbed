package astminer.examples

import astminer.cli.separateToken
import astminer.common.*
import astminer.common.model.LabeledPathContexts
import astminer.parse.antlr.javascript.JavaScriptMethodSplitter
import astminer.parse.antlr.javascript.JavaScriptParser
import astminer.parse.cpp.FuzzyCppParser
import astminer.parse.cpp.FuzzyMethodSplitter
import astminer.parse.java.GumTreeJavaParser
import astminer.paths.*
import com.google.gson.Gson
import java.io.File

data class Sample (val target: String, val func: String)

//Retrieve paths from all JavaScript files, using an Antlr parser.
//JavaScriptMethodSplitter is used to extract individual method nodes from the compilation unit tree.
fun code2vecCMethods(split: String, language: String) {
    val source = "../../../dataset/${split}.jsonl"
    val outputDir = "../code2vec/raws"

    val miner = PathMiner(PathRetrievalSettings(8, 3))

    val storage = Code2VecPathStorage(split, outputDir)

    File(source).forEachLine { line ->
        val sample = Gson().fromJson(line, Sample::class.java)
        val fileNode = when (language.toLowerCase()) {
            "java" -> {
                GumTreeJavaParser().parseInputStream(sample.func.byteInputStream())
            }
            "cpp", "c" -> {
                FuzzyCppParser().parseInputStream(sample.func.byteInputStream())
            }
            else -> {
                FuzzyCppParser().parseInputStream(sample.func.byteInputStream())
            }
        } ?: return@forEachLine
        fileNode.preOrder().forEach { it.setNormalizedToken(separateToken(it.getToken())) }

        val paths = miner.retrievePaths(fileNode)
        
        if (split.contains("train") && paths.isEmpty()) return@forEachLine

        var label = sample.target
        
        storage.store(
            LabeledPathContexts(
                label,
                paths.map { toPathContext(it) { node -> node.getNormalizedToken() } })
        )
    }
    storage.close()
}
