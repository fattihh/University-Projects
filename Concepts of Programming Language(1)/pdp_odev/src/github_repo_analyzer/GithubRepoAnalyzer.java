/**
*
* @author Fatih Uçar fatih.ucar1@ogr.sakarya.edu.tr
* @since 30.03.2024 - 06.04.2024
* <p>
* Bu sınıf repo nesnesini olusturur ve repo nesnesinin yöntemlerini içerir.
* analiz yöntemi haric yöntemler private tanımlanmıştır cünkü yöntemlerin disardan erisilmesini ve degistirilmesini istemiyorum.
* </p>
*/

package github_repo_analyzer;

import org.eclipse.jgit.api.Git;
import org.eclipse.jgit.api.errors.GitAPIException;
import java.io.File;
import java.io.IOException;
import java.nio.file.*;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.*;
import java.util.stream.Stream;
import java.io.BufferedReader;
import java.io.FileReader;

public class GithubRepoAnalyzer {
	private String repoUrl;
	private String cloneDirectoryPath;

	public GithubRepoAnalyzer(String repoUrl, String cloneDirectoryPath) {
		this.repoUrl = repoUrl;
		this.cloneDirectoryPath = cloneDirectoryPath;
	}

	public void cloneRepository() {
		try {
			System.out.println("Cloning repository... " + repoUrl);
			Git.cloneRepository().setURI(repoUrl).setDirectory(new File(cloneDirectoryPath)).call();
			System.out.println("Repository successfully cloned.");
		} catch (GitAPIException e) {
			e.printStackTrace();
		}
	}

	public List<Path> findClassPathsInJavaFiles(String cloneDirectoryPath) throws IOException {
		List<Path> classPaths = new ArrayList<>();

		Path startingPath = Paths.get(cloneDirectoryPath);
		try (Stream<Path> walkStream = Files.walk(startingPath)) {
			walkStream.filter(p -> p.toString().endsWith(".java")).forEach(filePath -> {
				String fileContent = "";
				try {
					fileContent = Files.readString(filePath);
				} catch (IOException e) {
					e.printStackTrace();
				}

				Pattern classPattern = Pattern.compile("class\\s+([A-Z][A-Za-z0-9]*)");
				Matcher matcher = classPattern.matcher(fileContent);

				if (matcher.find()) {
					classPaths.add(filePath);
				}
			});
		}

		return classPaths;
	}

	public void analyzeJavaFiles(List<Path> javaFiles) {
		for (Path javaFile : javaFiles) {
			try {
				int javadoc = countJavadocComments(javaFile.toString());
				int yorumsatiri = countSingleLineComments(javaFile.toString()) + commentBlocks(javaFile.toString());
				int codeLines = countCodeLines(javaFile.toString());
				int totalLines = countLoc(javaFile.toString());
				int functionCount = countFunctions(javaFile.toString());
				double percantage = calculateCommentDeviationPercentage(javaFile.toString());

				System.out.println("Sınıf: " + javaFile.getFileName());
				System.out.println("Javadoc Satır Sayısı: " + javadoc);
				System.out.println("Yorum Satırı Sayısı: " + yorumsatiri);
				System.out.println("Kod Satır Sayısı: " + codeLines);
				System.out.println("LOC: " + totalLines);
				System.out.println("Fonksiyon sayısı: " + functionCount);
				System.out.println("Yorum Sapma Yüzdesi:: " + percantage);
				// Fonksiyon sayısı ve Yorum Sapma Yüzdesi hesaplamaları burada yapılabilir

				System.out.println("------------------------------");
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	private int countJavadocComments(String filePath) throws IOException {
		Path path = Paths.get(filePath);

		if (!Files.exists(path) || !Files.isReadable(path)) {
			throw new IOException("Dosya bulunamadı veya okunamıyor: " + filePath);
		}

		int javadocLineCount = 0;
		boolean inJavadocComment = false;
		try (BufferedReader reader = Files.newBufferedReader(path)) {
			String line;

			while ((line = reader.readLine()) != null) {
				// String içindeki /** ve */ ifadelerini kontrol et
				String lineWithoutStrings = line.replaceAll("\".*?\"", "");

				// Aynı satırda başlayıp biten javadocları kontrol et
				if (lineWithoutStrings.trim().startsWith("/**") && lineWithoutStrings.trim().endsWith("*/")) {
					javadocLineCount++; // Başlangıç ve bitiş aynı satırda olduğunda
					continue;
				}

				if (!inJavadocComment && lineWithoutStrings.trim().startsWith("/**")) {
					inJavadocComment = true;
				} else if (inJavadocComment && lineWithoutStrings.trim().endsWith("*/")) {
					inJavadocComment = false;
				} else if (inJavadocComment) {
					// JavaDoc yorumunun içindeki her satırı say
					javadocLineCount++;
				}
			}
		}

		return javadocLineCount;
	}

	private int countSingleLineComments(String filePath) throws IOException {
		Path path = Paths.get(filePath);

		if (!Files.exists(path)) {
			throw new IOException("Dosya bulunamadı: " + filePath);
		}

		if (!Files.isReadable(path)) {
			throw new IOException("Dosya okunabilir değil: " + filePath);
		}

		int yorumSatiriSayisi = 0;

		try (Stream<String> lines = Files.lines(path)) {
			yorumSatiriSayisi = lines.mapToInt(satir -> {
				boolean stringIcinde = false; // Çift tırnak içinde miyiz?
				boolean charIcinde = false; // Tek tırnak içinde miyiz?
				boolean kaçış = false; // Kaçış karakteri mi?
				int yorumIndexi = -1;
				for (int i = 0; i < satir.length(); i++) {
					char c = satir.charAt(i);
					if (c == '\\' && !kaçış) { // Kaçış karakterini kontrol et
						kaçış = true;
					} else if (c == '"' && !kaçış && !charIcinde) { // Çift tırnak durumunu değiştir
						stringIcinde = !stringIcinde;
					} else if (c == '\'' && !kaçış && !stringIcinde) { // Tek tırnak durumunu değiştir
						charIcinde = !charIcinde;
					} else if (c == '/' && i + 1 < satir.length() && satir.charAt(i + 1) == '/' && !stringIcinde
							&& !charIcinde) { // Yorumu bul
						yorumIndexi = i;
						break;
					}
					kaçış = false; // Sıradaki karakter için kaçış durumunu sıfırla
				}
				return (yorumIndexi != -1) ? 1 : 0;
			}).sum();
		}

		return yorumSatiriSayisi;
	}

	private int commentBlocks(String filePath) {
		Path path = Paths.get(filePath);
		if (!Files.exists(path) || !Files.isReadable(path)) {
			System.err.println("Dosya bulunamadı veya okunamıyor: " + filePath);
			return 0;
		}

		StringBuilder contentBuilder = new StringBuilder();
		try (Stream<String> stream = Files.lines(path)) {
			stream.forEach(s -> contentBuilder.append(s).append("\n"));
		} catch (IOException e) {
			System.err.println("Dosya okunurken hata oluştu: " + e.getMessage());
			return 0;
		}

		String content = contentBuilder.toString();
		int totalCommentLines = 0;
		boolean inString = false;
		boolean escape = false; // Kaçış karakteri takibi için

		int i = 0;
		while (i < content.length()) {
			char c = content.charAt(i);
			if (c == '\\' && !escape) { // Kaçış karakteri varsa durumu değiştir
				escape = !inString; // String içindeyseniz ve kaçış karakteri ise
			} else if (c == '"' && !escape) {
				inString = !inString; // Çift tırnak durumunu değiştir
			} else if (!inString && c == '/' && i + 1 < content.length() && content.charAt(i + 1) == '*') {
				// Javadoc yorumlarını atla
				if (i + 2 < content.length() && content.charAt(i + 2) == '*') {
					i += 3; // Javadoc başlangıcını geç
					continue;
				}

				// Yorum bloğu başlangıcı bul
				int end = content.indexOf("*/", i + 2);
				if (end == -1) {
					System.err.println("Yorum bloğu kapanışı bulunamadı.");
					break;
				}

				String commentBlock = content.substring(i + 2, end).trim();
				long lineCount = commentBlock.lines().count();
				if (content.substring(i, end + 2).trim().lines().count() == 1) {
					lineCount = 1;
				}

				totalCommentLines += lineCount;
				i = end + 2;
				continue;
			}
			escape = false; // Sıradaki karakter için kaçış durumunu sıfırla
			i++;
		}

		return totalCommentLines;
	}

	private int countFunctions(String javaFilePath) throws IOException {
		Path path = Paths.get(javaFilePath); // String dosya yolunu Path nesnesine dönüştür
		String content = new String(Files.readAllBytes(path)); // Dosya içeriğini oku

		// Her iki düzenli ifadeyi kapsayan genişletilmiş düzenli ifade deseni
		String regexPattern = "(\\b[a-zA-Z_]\\w*\\s+\\b[a-zA-Z_]\\w*\\s*\\([^)]*\\)\\s*\\{)"
				+ "|(\\b[a-zA-Z_]\\w*\\s+\\b[a-zA-Z_]\\w*\\s*\\([^)]*\\)\\s*\\[\\])"
				+ "|((?s)(?<!\\w)(public|protected|private|static|final|synchronized|abstract)\\s+(<[^>]+>\\s+)?([\\w\\[\\]]+<.*?>[\\w\\[\\]]*\\s+)?[\\w\\[\\]]+\\s+\\w+\\s*\\(([^)]*?)\\)(?![\\w\\.]|\\{|\\->|;))";

		Pattern pattern = Pattern.compile(regexPattern, Pattern.DOTALL);
		Matcher matcher = pattern.matcher(content);

		int functionCount = 0;
		while (matcher.find()) {
			functionCount++;
		}

		return functionCount;
	}

	
	private int countCodeLines(String filePath) throws IOException {
        int codeLines = 0;
        boolean inComment = false;

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;

            while ((line = reader.readLine()) != null) {
                line = line.trim(); // Başındaki ve sonundaki boşlukları kaldır

                if (inComment) {
                    if (line.endsWith("*/")) {
                        inComment = false;
                        // Eğer yorum bloğu bitiş işaretiyle bitiyorsa ama başka kod da varsa, kod olarak say
                        if (!line.startsWith("*/")) {
                            codeLines++;
                        }
                    }
                    // Yorum bloğu içindeysek ve yukarıdaki koşulu karşılamıyorsa, bu satırı atla
                    continue;
                }

                // Yorum bloğu başlangıcı
                if (line.startsWith("/*") || line.startsWith("/**")) {
                    inComment = true;
                    // Yorum bloğu aynı satırda başlayıp bitiyorsa ve kod içeriyorsa, kod olarak say
                    if (line.contains("*/") && !line.endsWith("*/")) {
                        codeLines++;
                    }
                    continue;
                }
                // Tek satırlık yorumlar veya boş satırlar hariç tutulur
                if (line.startsWith("//") || line.isEmpty()) {
                    continue;
                }
                // Yukarıdaki koşullara uymayan satırlar kod satırıdır
                codeLines++;
            }
        }

        return codeLines;
    }

	
	

	
	
	

	private int countLoc(String filePath) throws IOException {
		int lines = 0;

		BufferedReader reader = new BufferedReader(new FileReader(filePath));
		while (reader.readLine() != null) {
			lines++;
		}

		reader.close();
		return lines;
	}

	private double calculateCommentDeviationPercentage(String filePath) throws IOException {
		int javadocLineCount = countJavadocComments(filePath);
		int commentCount = countSingleLineComments(filePath) + commentBlocks(filePath);
		int functionCount = countFunctions(filePath);
		int codeLines = countCodeLines(filePath);

		// Burada, bölme işlemi yapılırken, bölünen ya da bölen değerlerden birinin
		// double olmasını sağlıyoruz.
		// Bu, işlem sonucunun double türünde olmasını ve daha kesin bir sonuç elde
		// edilmesini sağlar.
		double YG = ((double) (javadocLineCount + commentCount) * 0.8) / functionCount;

		double YH = ((double) codeLines / functionCount) * 0.3;

		// Yine, double türünde bir hesaplama yaparak veri kaybını önlemiş oluyoruz.
		double percentage = (100 * YG) / YH - 100;

		percentage = Math.round(percentage * 100.0) / 100.0;

		return percentage;
	}

}