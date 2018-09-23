package il.ac.tau.cs.sw1.ex10.trivia;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Random;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.graphics.FontData;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

public class TriviaGUI {

	private static final int MAX_ERRORS = 3;
	private Shell shell;
	private Label scoreLabel;
	private Composite questionPanel;
	private Label startupMessageLabel;
	private Font boldFont;
	private String lastAnswer;
	
	private List<Map<String, List<String>>> questionToAnswersList;
	private int currentScore;
	private int currentQuestion;
	private int wrongStreak;
	private int usedPass;
	private int used5050;
	private boolean gameState;
	
	// Currently visible UI elements.
	Label instructionLabel;
	Label questionLabel;
	private List<Button> answerButtons = new LinkedList<>();
	private Button passButton;
	private Button fiftyFiftyButton;

	public void open() {
		createShell();
		runApplication();
	}

	/**
	 * Creates the widgets of the application main window
	 */
	private void createShell() {
		Display display = Display.getDefault();
		shell = new Shell(display);
		shell.setText("Trivia");

		// window style
		Rectangle monitor_bounds = shell.getMonitor().getBounds();
		shell.setSize(new Point(monitor_bounds.width / 3,
				monitor_bounds.height / 4));
		shell.setLayout(new GridLayout());

		FontData fontData = new FontData();
		fontData.setStyle(SWT.BOLD);
		boldFont = new Font(shell.getDisplay(), fontData);

		// create window panels
		createFileLoadingPanel();
		createScorePanel();
		createQuestionPanel();
	}

	/**
	 * Creates the widgets of the form for trivia file selection
	 */
	private void createFileLoadingPanel() {
		final Composite fileSelection = new Composite(shell, SWT.NULL);
		fileSelection.setLayoutData(GUIUtils.createFillGridData(1));
		fileSelection.setLayout(new GridLayout(4, false));

		final Label label = new Label(fileSelection, SWT.NONE);
		label.setText("Enter trivia file path: ");

		// text field to enter the file path
		final Text filePathField = new Text(fileSelection, SWT.SINGLE
				| SWT.BORDER);
		filePathField.setLayoutData(GUIUtils.createFillGridData(1));

		// "Browse" button
		final Button browseButton = new Button(fileSelection, SWT.PUSH);
		browseButton.setText("Browse");
		browseButton.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e){
				filePathField.setText(GUIUtils.getFilePathFromFileDialog(shell));
			}
		});

		// "Play!" button
		final Button playButton = new Button(fileSelection, SWT.PUSH);
		playButton.setText("Play!");
		playButton.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e){
				if (loadQuestions(filePathField.getText())) {
					gameState = true;
					Collections.shuffle(questionToAnswersList);
					lastAnswer = "";
					currentScore = 0;
					wrongStreak = 0;
					currentQuestion = 0;
					used5050 = 0;
					usedPass = 0;
					nextQuestion();
				}
			}
		});
	}

	/**
	 * Check if given answer is the correct one
	 */
	private boolean isCorrectAnswer(String answer, String correct){
		return answer.equals(correct);
	}
	
	/**
	 * Loads the questions and answers from the given file
	 */
	private boolean loadQuestions(String path){
		if (this.questionToAnswersList != null)// Reuse the Set if possible
			this.questionToAnswersList.clear();
		else
			this.questionToAnswersList = new ArrayList<>();
		BufferedReader buffReader;
		String line;
		String[] words;
		Map<String,List<String>> questionToAnswers;
		List<String> answers;
		try {
			buffReader = new BufferedReader(new FileReader(path));
		try {
			while ((line = buffReader.readLine()) != null){
				words = line.split("\t");
				if (words.length != 5){
					buffReader.close();
					throw new IOException();
				}
				questionToAnswers = new HashMap<>();
				answers = new ArrayList<>();
				for (int i = 1; i < words.length; i++){
					answers.add(words[i]);
				}
				questionToAnswers.put(words[0], answers);
				if (!this.questionToAnswersList.contains(questionToAnswers))
					this.questionToAnswersList.add(questionToAnswers);
			}
			buffReader.close();
			return true;
		} catch (IOException e) {
			GUIUtils.showErrorDialog(shell, "Trivia file format error: Trivia "
					+ "file row must contain a question and four answers,"
					+ "seperated by tabs. (row 1)");
			return false;
		}
		} catch (FileNotFoundException e) {
			GUIUtils.showErrorDialog(shell, "File not found!" + System.lineSeparator() + "Please check given path");
			return false;
		}
	}
	
	/**
	 * Creates the panel that displays the current score
	 */
	private void createScorePanel() {
		Composite scorePanel = new Composite(shell, SWT.BORDER);
		scorePanel.setLayoutData(GUIUtils.createFillGridData(1));
		scorePanel.setLayout(new GridLayout(2, false));

		final Label label = new Label(scorePanel, SWT.NONE);
		label.setText("Total score: ");

		// The label which displays the score; initially empty
		scoreLabel = new Label(scorePanel, SWT.NONE);
		scoreLabel.setLayoutData(GUIUtils.createFillGridData(1));
	}

	/**
	 * Creates the panel that displays the questions, as soon as the game
	 * starts. See the updateQuestionPanel for creating the question and answer
	 * buttons
	 */
	private void createQuestionPanel() {
		questionPanel = new Composite(shell, SWT.BORDER);
		questionPanel.setLayoutData(new GridData(GridData.FILL, GridData.FILL,
				true, true));
		questionPanel.setLayout(new GridLayout(2, true));

		// Initially, only displays a message
		startupMessageLabel = new Label(questionPanel, SWT.NONE);
		startupMessageLabel.setText("No question to display, yet.");
		startupMessageLabel.setLayoutData(GUIUtils.createFillGridData(2));
	}

	/**
	 * Serves to display the question and answer buttons
	 */
	private void updateQuestionPanel(String question, List<String> answers) {
		// Save current list of answers.
		final String correctAnswer = answers.get(0);
		final List<String> currentAnswers = answers;
		Collections.shuffle(currentAnswers);
		scoreLabel.setText(Integer.toString(currentScore));
		answerButtons.clear();
		
		// clear the question panel
		Control[] children = questionPanel.getChildren();
		for (Control control : children) {
			control.dispose();
		}

		// create the instruction label
		instructionLabel = new Label(questionPanel, SWT.CENTER | SWT.WRAP);
		instructionLabel.setText(lastAnswer + "Answer the following question:");
		instructionLabel.setLayoutData(GUIUtils.createFillGridData(2));

		// create the question label
		questionLabel = new Label(questionPanel, SWT.CENTER | SWT.WRAP);
		questionLabel.setText(question);
		questionLabel.setFont(boldFont);
		questionLabel.setLayoutData(GUIUtils.createFillGridData(2));

		// create the answer buttons
		for (int i = 0; i < 4; i++) {
			final Button answerButton = new Button(questionPanel, SWT.PUSH | SWT.WRAP);
			answerButton.setText(answers.get(i));
			GridData answerLayoutData = GUIUtils.createFillGridData(1);
			answerLayoutData.verticalAlignment = SWT.FILL;
			answerButton.setLayoutData(answerLayoutData);
			answerButton.addSelectionListener(new SelectionAdapter() {
				public void widgetSelected(SelectionEvent e){
					if (gameState) {
						if (isCorrectAnswer(answerButton.getText(), correctAnswer)) {
							currentScore += 3;
							lastAnswer = "Correct! ";
							wrongStreak = 0;
						} else {
							currentScore -= 2;
							wrongStreak++;
							lastAnswer = "Wrong... ";
						}
						scoreLabel.setText(Integer.toString(currentScore));
						nextQuestion();
					}
				}
			});
			
			answerButtons.add(answerButton);
		}

		// create the "Pass" button to skip a question
		passButton = new Button(questionPanel, SWT.PUSH);
		passButton.setText("Pass");
		GridData data = new GridData(GridData.END, GridData.CENTER, true,
				false);
		data.horizontalSpan = 1;
		passButton.setLayoutData(data);
		passButton.setEnabled(isButtonEnabled("pass"));
		passButton.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e){
				if (gameState){
					if (usedPass > 0){
						currentScore--;
						scoreLabel.setText(Integer.toString(currentScore));
					}
					usedPass++;
					nextQuestion();
				}
			}
		});
		
		
		// create the "50-50" button to show fewer answer options
		fiftyFiftyButton = new Button(questionPanel, SWT.PUSH);
		fiftyFiftyButton.setText("50-50");
		data = new GridData(GridData.BEGINNING, GridData.CENTER, true,
				false);
		data.horizontalSpan = 1;
		fiftyFiftyButton.setLayoutData(data);
		fiftyFiftyButton.setEnabled(isButtonEnabled("5050"));
		fiftyFiftyButton.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e){
				if (gameState){
					if (used5050 > 0)
					{
						currentScore--;
						scoreLabel.setText(Integer.toString(currentScore));
					}
					used5050++;
					Random rand = new Random();
					int count = 0;
					int i;
					while (count < 2) {
						i = rand.nextInt(3);
						if (!currentAnswers.get(i).equals(correctAnswer)) {
							if (answerButtons.get(i).getEnabled()){
								answerButtons.get(i).setEnabled(false);
								count++;
							}
						}
					}
					fiftyFiftyButton.setEnabled(false);
					passButton.setEnabled(isButtonEnabled("pass"));
				}
			}
		});

		// two operations to make the new widgets display properly
		questionPanel.pack();
		questionPanel.getParent().layout();
	}

	/**
	 * Check if the user is able to press button
	 */
	private boolean isButtonEnabled(String buttonName){
		int used = 0;
		if (buttonName.equals("pass")){
			used = usedPass;
		}
		if (buttonName.equals("5050")){
			used = used5050;
		}
		if (used == 0)
			return true;
		if (currentScore > 0)
			return true;
		return false;
	}
	
	/**
	 * Loads next question
	 */
	private void nextQuestion(){
		if ((wrongStreak == MAX_ERRORS) || (currentQuestion == questionToAnswersList.size())){
			GUIUtils.showInfoDialog(shell, "GAME OVER", "Your final"
					+ " score is " + currentScore + " after " + 
					(currentQuestion-usedPass) + " questions");
			gameState = false;
		}
		else{
			String newQuestion = (String)questionToAnswersList.get(currentQuestion).keySet().toArray()[0];
			updateQuestionPanel(newQuestion, questionToAnswersList.get(currentQuestion++).get(newQuestion));
		}
	}
	
	/**
	 * Opens the main window and executes the event loop of the application
	 */
	private void runApplication() {
		shell.open();
		Display display = shell.getDisplay();
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch())
				display.sleep();
		}
		display.dispose();
		boldFont.dispose();
	}
}
